using System;
using System.Collections.Generic;
using System.Net;
using System.Net.Sockets;
using System.Text;
using UnityEngine;

namespace ServerCore
{
	public class Connector
	{
        //Func 대리자 왼쪽부터 입력 매개변수, 맨 오른쪽이 반환값이다.
		Func<Session> _sessionFactory;

        
		public void Connect(IPEndPoint endPoint, Func<Session> sessionFactory, int count = 1)
		{
			for (int i = 0; i < count; i++)
			{
				
				Socket socket = new Socket(endPoint.AddressFamily, SocketType.Stream, ProtocolType.Tcp);
				_sessionFactory = sessionFactory;

                //SocketAsyncEventArgs의 목적은 소켓 응용프로그램에서 사용하는 비동기 패턴을 제공
                //Send.Receieve에 사용할 수 있고 Pooling도 가능하다.

                SocketAsyncEventArgs args = new SocketAsyncEventArgs();

                //받음 완료 이벤트 연결 -> 해당 소켓에서 오는 데이터가 있다면 연결된 이벤트를 실행한다. 
				args.Completed += OnConnectCompleted;

                //비동기 작업의 원격IP EndPoint를 지정한다.
				args.RemoteEndPoint = endPoint;

                //비동기소켓 작업과 연결된 사용자 또는 애플리케이션 개체를 가져오거나 설정
				args.UserToken = socket;

				RegisterConnect(args);
			}
		}

		void RegisterConnect(SocketAsyncEventArgs args)
		{
            //UserToken을 Socket으로 캐스팅
			Socket socket = args.UserToken as Socket;

			if (socket == null)
				return;

            //원격 호스트연결에 대한 비동기 요청을 시작한다.
			bool pending = socket.ConnectAsync(args);

			if (pending == false)
				OnConnectCompleted(null, args);
		}

		void OnConnectCompleted(object sender, SocketAsyncEventArgs args)
		{
            //SocketError : 비동기 소켓 작업의 결과를 가져오거나 설정

            if (args.SocketError == SocketError.Success)
			{
				Session session = _sessionFactory.Invoke();
				session.Start(args.ConnectSocket);
				session.OnConnected(args.RemoteEndPoint);
			}
			else
			{
				Debug.Log($"OnConnectCompleted Fail: {args.SocketError}");
			}
		}
	}
}
