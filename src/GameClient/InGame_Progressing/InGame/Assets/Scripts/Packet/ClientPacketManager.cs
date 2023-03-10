using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Google.Protobuf;
using Google.Protobuf.Protocol;

/*
마샬링이란 한 객체의 메모리에서의 표현방식을 저장 또는 전송에 적합한 다른 데이터 형식으로 변환하는 과정이다.
직렬화와 유사하다. 복잡한 통신을 단순화하여 쉽게 데이터를 주고 받게 하기 위함.

C#으로 작성되는 코드는 ManagedCode, 전통적인 C/C++ 컴파일러에 의해 컴파일되는 코드는 UnManagedCode
Managed Code는 GC(Garbage Collector)에 의해 정리가 되는 메모리 반대는 프로그램 코드나 운영체제에 의해 정리가 된다.

*/

class PacketManager
{
    static PacketManager _instance = new PacketManager();
    public static PacketManager Instance { get { return _instance; } }

    Dictionary<ushort, Action<byte[], uint, ushort>> recv = new Dictionary<ushort, Action<byte[], uint, ushort>>();
    Dictionary<ushort, Action<IMessage>> handler = new Dictionary<ushort, Action<IMessage>>();

    int time = (ushort)INGAME.Time;

    //Action<ushort, IMessage> customHandler = (ushort id, IMessage message) => { PacketQueue.Instance.Push(id, message); };
    public Action<ushort, IMessage> customHandler { get; set; }

    PacketManager()
    {
        recv.Add((ushort)INGAME.Time, MakePacket<Times>);
        handler.Add((ushort)INGAME.Time, PacketHandler.RTTSync);

        recv.Add((ushort)INGAME.Start, MakePacket<StartData>);
        handler.Add((ushort)INGAME.Start, PacketHandler.GameStart);

        recv.Add((ushort)INGAME.PlayerSync, MakePacket<MoveData>);
        handler.Add((ushort)INGAME.PlayerSync, PacketHandler.PlayersSync);

        recv.Add((ushort)INGAME.Connect, MakePacket<Player>);
        handler.Add((ushort)INGAME.Connect, PacketHandler.GameConnect);

        recv.Add((ushort)INGAME.ObstacleMove, MakePacket<Move>);
        handler.Add((ushort)INGAME.ObstacleMove, PacketHandler.ObtacleMove);

        recv.Add((ushort)INGAME.GetTick, MakePacket<Times>);
        handler.Add((ushort)INGAME.GetTick, PacketHandler.TimeSync);

        recv.Add((ushort)INGAME.ConnectFail, MakePacket<ConnectData>);
        handler.Add((ushort)INGAME.ConnectFail, PacketHandler.CnnectFail);

        recv.Add((ushort)INGAME.GameComplte, MakePacket<PlayerGoalData>);
        handler.Add((ushort)INGAME.GameComplte, PacketHandler.GameComplete);

        recv.Add((ushort)INGAME.GameEnd, MakePacket<PlayerGoalData>);
        handler.Add((ushort)INGAME.GameEnd, PacketHandler.GameEnds);

        recv.Add((ushort)INGAME.PlayerGoal, MakePacket<PlayerGoalData>);
        handler.Add((ushort)INGAME.PlayerGoal, PacketHandler.PlayerGoal);

        recv.Add((ushort)INGAME.Reconnect, MakePacket<ConnectData>);
        handler.Add((ushort)INGAME.Reconnect, PacketHandler.ReConnect);

        recv.Add((ushort)INGAME.PlayerDrop, MakePacket<Move>);
        handler.Add((ushort)INGAME.PlayerDrop, PacketHandler.PlayerFail);
    }

    public void OnReceievePacket(byte[] buffer, Pkt_Head head)
    {
        //UnityEngine.Debug.Log("Head size: " + head.size + "Head type:" + head.type);

        Action<byte[], uint, ushort> action = null;
        if (recv.TryGetValue((ushort)head.type, out action))
            action.Invoke(buffer, head.size, (ushort)head.type);
    }

    void MakePacket<T>(byte[] data, uint len, ushort id) where T : IMessage, new()
    {
        int size = Marshal.SizeOf<Pkt_Head>();

        T pkt = new T();
        pkt.MergeFrom(data, size, (int)len);

        customHandler.Invoke(id, pkt);
    }

    public Action<IMessage> GetHandler(ushort id)
    {
        Action<IMessage> action = null;
        if (handler.TryGetValue(id, out action))
            return action;
        return null;
    }
}
public struct Pkt_Head
{
    //헤더를 제외한 사이즈
    public uint size;
    public INGAME type;
};