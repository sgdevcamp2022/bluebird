using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Google.Protobuf;
using Google.Protobuf.Protocol;


//마샬링이란 한 객체의 메모리에서의 표현방식을 저장 또는 전송에 적합한 다른 데이터 형식으로 변환하는 과정이다.
//직렬화와 유사하다. 복잡한 통신을 단순화하여 쉽게 데이터를 주고 받게 하기 위함.

//C#으로 작성되는 코드는 ManagedCode, 전통적인 C/C++ 컴파일러에 의해 컴파일되는 코드는 UnManagedCode
//Managed Code는 GC(Garbage Collector)에 의해 정리가 되는 메모리 반대는 프로그램 코드나 운영체제에 의해 정리가 된다.

class PacketManager
{
    static PacketManager _instance = new PacketManager();
    public static PacketManager Instance { get { return _instance; } }

    Dictionary<ushort, Action<byte[], uint, ushort>> recv = new Dictionary<ushort, Action<byte[], uint, ushort>>();
    Dictionary<ushort, Action<IMessage>> handler = new Dictionary<ushort, Action<IMessage>>();

    Action<ushort, IMessage> customHandler = (ushort id, IMessage message) => { PacketQueue.Instance.Push(id, message); };

    PacketManager() {
        recv.Add((ushort)INGAME.Start, MakePacket<Data>);
        handler.Add((ushort)INGAME.Start, PacketHandler.GameStart);
        recv.Add((ushort)INGAME.Move, MakePacket<Data>);
        handler.Add((ushort)INGAME.Move, PacketHandler.PlayerMove);
        recv.Add((ushort)INGAME.Connect, MakePacket<Data>);
        handler.Add((ushort)INGAME.Connect, PacketHandler.GameConnect);
        recv.Add((ushort)INGAME.ObstacleMove, MakePacket<Data>);
        handler.Add((ushort)INGAME.ObstacleMove, PacketHandler.ObtacleMove);
    }

    public byte[] Make_login_handler(Data pkt, INGAME type)
    {
        Pkt_Head head = new Pkt_Head();
        head.type = type;

        //마샬링에 필요한 만큼의 개체 크기를 반환
        int size = Marshal.SizeOf<Pkt_Head>();

        //Pkt_Head.size = data의 사이즈
        //패킷 사이즈 = head 사이즈 + data 사이즈
        head.size = (uint)pkt.CalculateSize();
        byte[] send_buffer = new byte[head.size + size];

        //지정된 바이트 수를 사용하여 프로세스의 관리되지 않는 메모리에서 메로리를 할당 즉, buffsize만큼 Unmanaged 메모리 할당
        //관리되는 개체의 데이터를 관리되지 않는 메모리 블록으로 마샬링합니다.
        //ptr 포인터에 저장되어 있는 주소의 위치를 참조, 이를 size만큼 복사하여 send_buffer에 집어 넣는다.
        //할당된 IntPtr unmanaged 메모리를 해제한다.

        IntPtr ptr = Marshal.AllocHGlobal(size);
        Marshal.StructureToPtr(head, ptr, true);
        Marshal.Copy(ptr, send_buffer, 0, size);
        Marshal.FreeHGlobal(ptr);

        //pkt값을 send_buffer에 복사?
        Array.Copy(pkt.ToByteArray(), 0, send_buffer, size, head.size);
        return send_buffer;
    }
    //https://technodori.tistory.com/entry/C-byte-%EA%B5%AC%EC%A1%B0%EC%B2%B4-%EA%B5%AC%EC%A1%B0%EC%B2%B4-byte
    //버퍼에서는 한바이트씩 포인터로 이동해서 참조를 한다.
    //receieve데이터를 받으면, 헤더 사이즈를 찾아야함.

    public void OnReceievePacket(byte[] packet, int len)
    {
        int size = Marshal.SizeOf<Pkt_Head>();

        Pkt_Head head = new Pkt_Head();
        //배열의 크기만큼 비관리 메모리 영역에 메모리 할당
        //배열에 저장된 데이터를 위에서 할당한 메모리 영역에 복사한다.
        //복사한 데이터를 구조체 객체로 변환
        //비관리 메모리 영역에 할당했던 메모리를 해제

        IntPtr ptr = Marshal.AllocHGlobal(size);
        Marshal.Copy(packet, 0, ptr, size);
        head = (Pkt_Head)Marshal.PtrToStructure(ptr, typeof(Pkt_Head));
        Marshal.FreeHGlobal(ptr);

        //여기까지 헤더의 길이와 타입을 알아낼 수 있다.

        UnityEngine.Debug.Log("Head size: " + head.size + "Head type:" + head.type);

        Action<byte[], uint, ushort> action = null;
        if (recv.TryGetValue((ushort)head.type, out action))
            action.Invoke(packet, head.size, (ushort)head.type);
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

struct Pkt_Head
{
    //헤더를 제외한 사이즈
    public uint size;
    public INGAME type;
};