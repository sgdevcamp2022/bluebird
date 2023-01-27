using Google.Protobuf;
using Google.Protobuf.Protocol;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

public class PacketMessage
{
    public ushort Id { get; set; }
    public IMessage Message { get; set; }
}

public class PacketQueue
{
    static PacketQueue packetQueue = new PacketQueue();
    public static PacketQueue Instance{ get { return packetQueue; } }  

    Queue<PacketMessage> packets = new Queue<PacketMessage>();

    object _lock = new object();

    public void Push(ushort id, IMessage message)
    {
        lock (_lock)
        {
            packets.Enqueue(new PacketMessage() { Id = id, Message = message });
        }
    }

    public PacketMessage Pop()
    {
        lock (_lock)
        {
            if (packets.Count == 0)
                return null;

            return packets.Dequeue();
        }
    }

    public List<PacketMessage> PopAll()
    {
        List<PacketMessage> list = new List<PacketMessage>();
        lock (_lock)
        {
            while (packets.Count > 0)
                list.Add(packets.Dequeue());
        }
        return list;
    }
}
