using System;
using System.Collections.Generic;
using System.Drawing;
using System.Net;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using UnityEngine;

namespace ServerCore
{
	public abstract class PacketSession : Session
	{
		public static readonly int HeaderSize = Marshal.SizeOf<Pkt_Head>();
		public sealed override int OnRecv(ArraySegment<byte> buffer)
		{
			int processLen = 0;
			while (true)
			{
				
				// 최소한 헤더는 파싱할 수 있는지 확인
				if (buffer.Count < HeaderSize)
					break;

                // 패킷이 완전체로 도착했는지 확인

                //offset: ArraySegment로 구분된 범위의 첫 번째 요소 위치를 가져옴
                //Array: ArraySegment가 구분하는 범위의 요소가 포함된 원본 배열을 가져옵니다.
                //Count : 요소 수를 가져옴
                Pkt_Head head = new Pkt_Head();

                IntPtr ptr = Marshal.AllocHGlobal(HeaderSize);
                Marshal.Copy(buffer.Array, 0, ptr, HeaderSize);
                head = (Pkt_Head)Marshal.PtrToStructure(ptr, typeof(Pkt_Head));
                Marshal.FreeHGlobal(ptr);

				if ((buffer.Count - HeaderSize) < head.size)
					break;

				int total = (int)head.size + HeaderSize;
				// 여기까지 왔으면 패킷 조립 가능
				OnRecvPacket(new ArraySegment<byte>(buffer.Array, buffer.Offset + HeaderSize, (int)head.size), head);

				processLen += total;
				buffer = new ArraySegment<byte>(buffer.Array, buffer.Offset + total, buffer.Count - total);
			}

			return (int)processLen;
		}

		public abstract void OnRecvPacket(ArraySegment<byte> buffer, Pkt_Head head);
	}

	public abstract class Session
	{
		Socket _socket;
		int _disconnected = 0;

		RecvBuffer _recvBuffer = new RecvBuffer(65535);

		object _lock = new object();
		Queue<ArraySegment<byte>> _sendQueue = new Queue<ArraySegment<byte>>();
		List<ArraySegment<byte>> _pendingList = new List<ArraySegment<byte>>();
		SocketAsyncEventArgs _sendArgs = new SocketAsyncEventArgs();
		SocketAsyncEventArgs _recvArgs = new SocketAsyncEventArgs();

		public abstract void OnConnected(EndPoint endPoint);
		public abstract int  OnRecv(ArraySegment<byte> buffer);
		public abstract void OnSend(int numOfBytes);
		public abstract void OnDisconnected(EndPoint endPoint);

		void Clear()
		{
            //lock 블럭안의 코드는 한번에 하나의 쓰레드만 실행
			lock (_lock)
			{
				_sendQueue.Clear();
				_pendingList.Clear();
			}
		}

		public void Start(Socket socket)
		{
			_socket = socket;

			_recvArgs.Completed += new EventHandler<SocketAsyncEventArgs>(OnRecvCompleted);
			_sendArgs.Completed += new EventHandler<SocketAsyncEventArgs>(OnSendCompleted);

			RegisterRecv();
		}

		public void Send(List<ArraySegment<byte>> sendBuffList)
		{
			if (sendBuffList.Count == 0)
				return;

			lock (_lock)
			{
				foreach (ArraySegment<byte> sendBuff in sendBuffList)
					_sendQueue.Enqueue(sendBuff);

                //보류중인 연결 요청이 0이라면
				if (_pendingList.Count == 0)
					RegisterSend();
			}
		}

		public void Send(ArraySegment<byte> sendBuff)
		{
			lock (_lock)
			{
				_sendQueue.Enqueue(sendBuff);
				if (_pendingList.Count == 0)
					RegisterSend();
			}
		}

		public void Disconnect()
		{
            //Interlocked: 다중 스레드에서 공유하는 변수에 대한 원자 단위 연산을 제공한다.
            //Critical Section 내의 공유 자원의 변수에 대한 원자성을 보장한다.
            
            //Exchange: 원자성 연산으로 매개변수를 지정된 값으로 설정하고 원래 값을 반환한다.
			if (Interlocked.Exchange(ref _disconnected, 1) == 1)
				return;

			OnDisconnected(_socket.RemoteEndPoint);
            //소켓에서 보내기 및 받기를 사용할 수 없도록 설정한다.
			_socket.Shutdown(SocketShutdown.Both);
			_socket.Close();
			Clear();
		}

		#region 네트워크 통신

		void RegisterSend()
		{
			if (_disconnected == 1)
				return;

			while (_sendQueue.Count > 0)
			{
				ArraySegment<byte> buff = _sendQueue.Dequeue();
				_pendingList.Add(buff);
			}
            //비동기 소켓 메서드에 사용할 데이터 버퍼의 배열을 가져오거나 설정
			_sendArgs.BufferList = _pendingList;

			try
			{
                //연결된 소켓에 데이터를 보냅니다
				bool pending = _socket.SendAsync(_sendArgs);
				if (pending == false)
					OnSendCompleted(null, _sendArgs);
			}
			catch (Exception e)
			{
				Debug.Log($"RegisterSend Failed {e}");
			}
		}

		void OnSendCompleted(object sender, SocketAsyncEventArgs args)
		{
			lock (_lock)
			{
                //BytesTransferred : 소켓작업에서 전송된 바이트 수를 가져온다.
                if (args.BytesTransferred > 0 && args.SocketError == SocketError.Success)
				{
					try
					{
						_sendArgs.BufferList = null;
						_pendingList.Clear();

						OnSend(_sendArgs.BytesTransferred);

						if (_sendQueue.Count > 0)
							RegisterSend();
					}
					catch (Exception e)
					{
                        Debug.Log($"OnSendCompleted Failed {e}");
					}
				}
				else
				{
					Disconnect();
				}
			}
		}

		void RegisterRecv()
		{
			if (_disconnected == 1)
				return;

			_recvBuffer.Clean();
			ArraySegment<byte> segment = _recvBuffer.WriteSegment;
			_recvArgs.SetBuffer(segment.Array, segment.Offset, segment.Count);

			try
			{
				bool pending = _socket.ReceiveAsync(_recvArgs);
				if (pending == false)
					OnRecvCompleted(null, _recvArgs);
			}
			catch (Exception e)
			{
                Debug.Log($"RegisterRecv Failed {e}");
			}
		}

		void OnRecvCompleted(object sender, SocketAsyncEventArgs args)
		{
			if (args.BytesTransferred > 0 && args.SocketError == SocketError.Success)
			{
				try
				{
					// Write 커서 이동
					if (_recvBuffer.OnWrite(args.BytesTransferred) == false)
					{
						UnityEngine.Debug.Log("OnWrite Disconnect");
						Disconnect();
						return;
					}

					// 컨텐츠 쪽으로 데이터를 넘겨주고 얼마나 처리했는지 받는다
					int processLen = OnRecv(_recvBuffer.ReadSegment);
					if (processLen < 0 || _recvBuffer.DataSize < processLen)
					{
                        UnityEngine.Debug.Log("OnRecv Disconnect");
                        Disconnect();
						return;
					}

					// Read 커서 이동
					if (_recvBuffer.OnRead(processLen) == false)
					{
                        UnityEngine.Debug.Log("OnRead Disconnect");
                        Disconnect();
						return;
					}

					RegisterRecv();
				}
				catch (Exception e)
				{
                    Debug.Log($"OnRecvCompleted Failed {e}");
				}
			}
			else
			{
				UnityEngine.Debug.Log(args.BytesTransferred + " " + args.SocketError);
                //RegisterRecv();
                Disconnect();
            }
		}

		#endregion
	}
}
