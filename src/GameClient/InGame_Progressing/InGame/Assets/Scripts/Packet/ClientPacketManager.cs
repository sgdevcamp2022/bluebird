using Google.Protobuf;
using Google.Protobuf.Protocol;
using ServerCore;
using System;
using System.Collections.Generic;

class PacketManager
{
    //region을 접어도 설명이 나타난다.
	#region Singleton
	static PacketManager _instance = new PacketManager();
	public static PacketManager Instance { get { return _instance; } }
	#endregion

	PacketManager()
	{
		Register();
	}

    //Dictionary는 Key와 Value 세트의 연관배열, Key를 사용해 Value 값을 얻을 수 있다.
    //ushort 부호가 없는 short
    //Delegate(델리게이트,대리자) : 함수를 변수에 담고 싶을때 사용하는것이 대리자이다. +=, -= 을 통해 메소드를 추가 또는 뺄 수 있다. 델리게이트를 하나 실행하면 여러개의 메소드가 실행
    //될 수 있다.
    //Action 대리자는 리턴 값이 없을때만 사용이 가능하다. <> 안에 매개변수를 넣는다.
    Dictionary<ushort, Action<PacketSession, ArraySegment<byte>, ushort>> _onRecv = new Dictionary<ushort, Action<PacketSession, ArraySegment<byte>, ushort>>();
	Dictionary<ushort, Action<PacketSession, IMessage>> _handler = new Dictionary<ushort, Action<PacketSession, IMessage>>();
		
	public void Register()
	{		
        //Add를 통해 Dictionary에 요소 추가
		_onRecv.Add((ushort)INGAME.Connect, MakePacket<Data>);
		_handler.Add((ushort)INGAME.Connect, PacketHandler.S_ChatHandler);		
	
	}

	public void OnRecvPacket(PacketSession session, ArraySegment<byte> buffer)
	{
		ushort count = 0;

		ushort size = BitConverter.ToUInt16(buffer.Array, buffer.Offset);
		count += 2;
		ushort id = BitConverter.ToUInt16(buffer.Array, buffer.Offset + count);
		count += 2;

		Action<PacketSession, ArraySegment<byte>, ushort> action = null;
		if (_onRecv.TryGetValue(id, out action))
			action.Invoke(session, buffer, id);
	}

	void MakePacket<T>(PacketSession session, ArraySegment<byte> buffer, ushort id) where T : IMessage, new()
	{
		T pkt = new T();
		pkt.MergeFrom(buffer.Array, buffer.Offset + 4, buffer.Count - 4);
		Action<PacketSession, IMessage> action = null;

        //지정한 키와 연결된 값을 가져온다.
        //메인 스레드에서 지정된 대리자를 실행한다.
        if (_handler.TryGetValue(id, out action))
			action.Invoke(session, pkt);
	}

	public Action<PacketSession, IMessage> GetPacketHandler(ushort id)
	{
		Action<PacketSession, IMessage> action = null;
		if (_handler.TryGetValue(id, out action))
			return action;
		return null;
	}
}