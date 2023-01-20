using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net.Sockets;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using Google.Protobuf;
using Google.Protobuf.Protocol;

//마샬링이란 한 객체의 메모리에서의 표현방식을 저장 또는 전송에 적합한 다른 데이터 형식으로 변환하는 과정이다.
//직렬화와 유사하다. 복잡한 통신을 단순화하여 쉽게 데이터를 주고 받게 하기 위함.

//C#으로 작성되는 코드는 ManagedCode, 전통적인 C/C++ 컴파일러에 의해 컴파일되는 코드는 UnManagedCode
//Managed Code는 GC(Garbage Collector)에 의해 정리가 되는 메모리 반대는 프로그램 코드나 운영체제에 의해 정리가 된다.


class PacketHandler
{
    public static PacketHandler Instance = new PacketHandler();


    public static byte[] Make_login_handler(Data pkt)
    {
        Pkt_Head head = new Pkt_Head();

        //마샬링에 필요한 만큼의 개체 크기를 반환
        int size = Marshal.SizeOf<Pkt_Head>();
        
        //패킷 사이즈 = pkt 의 사이즈
        head.size = (uint)pkt.CalculateSize();
        byte[] send_buffer = new byte[head.size + size];

        //지정된 바이트 수를 사용하여 프로세스의 관리되지 않느 메모리에서 메로리를 할당 즉, buffsize만큼 Unmanaged 메모리 할당
        IntPtr ptr = Marshal.AllocHGlobal(size);
        //관리되는 개체의 데이터를 관리되지 않는 메모리 블록으로 마샬링합니다.
        Marshal.StructureToPtr(head, ptr, true);
        //ptr 포인터에 저장되어 있는 주소의 위치를 참조, 이를 size만큼 복사하여 send_buffer에 집어 넣는다.
        Marshal.Copy(ptr, send_buffer, 0, size);
        //할당된 IntPtr unmanaged 메모리를 해제한다.
        Marshal.FreeHGlobal(ptr);

        //pkt값을 send_buffer에 복사?
        Array.Copy(pkt.ToByteArray(), 0, send_buffer, size, head.size);

        return send_buffer;
    }

    public static byte[] Make_login_handler(Player pkt)
    {
        Pkt_Head head = new Pkt_Head();

        //마샬링에 필요한 만큼의 개체 크기를 반환
        int size = Marshal.SizeOf<Pkt_Head>();
        //패킷 사이즈?
        head.size = (uint)pkt.CalculateSize();
        byte[] send_buffer = new byte[head.size + size];

        //지정된 바이트 수를 사용하여 프로세스의 관리되지 않느 메모리에서 메로리를 할당 즉, buffsize만큼 Unmanaged 메모리 할당
        IntPtr ptr = Marshal.AllocHGlobal(size);
        //관리되는 개체의 데이터를 관리되지 않는 메모리 블록으로 마샬링합니다.
        Marshal.StructureToPtr(head, ptr, true);
        //ptr 포인터에 저장되어 있는 주소의 위치를 참조, 이를 size만큼 복사하여 send_buffer에 집어 넣는다.
        Marshal.Copy(ptr, send_buffer, 0, size);
        //할당된 IntPtr unmanaged 메모리를 해제한다.
        Marshal.FreeHGlobal(ptr);

        //pkt값을 send_buffer에 복사?
        Array.Copy(pkt.ToByteArray(), 0, send_buffer, size, head.size);

        return send_buffer;
    }
}
struct Pkt_Head
{
    public uint size;
    public INGAME type;
};