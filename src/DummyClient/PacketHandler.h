#pragma once

class PacketHandler
{
public:
	static void HandlerPacket(SessionRef ref, BYTE* buffer, int32 len);

	static SendBufferRef MakeSendBuffer(Protocol::S_DATA ptr, Protocol::STATE type);

private:
	static void HandlerLogin(SessionRef ref, Protocol::S_DATA&& pkt);
};

struct Pkt_Header {
	google::protobuf::uint32 size;
	Protocol::STATE type;
};

template<typename T>
inline SendBufferRef _MakeSendBuffer(T& ptr, Protocol::STATE type)
{
	const uint16 data_size = static_cast<uint16>(ptr.ByteSizeLong());
	const uint16 packet_size = data_size + sizeof(Pkt_Header);

	SendBufferRef send_buffer = make_shared<SendBuffer>(packet_size);
	Pkt_Header* header = reinterpret_cast<Pkt_Header*>(send_buffer->Buffer());
	header->size = data_size;
	header->type = type;
	ptr.SerializeToArray(&header[1], data_size);
	send_buffer->Close(packet_size);

	return send_buffer;
}

template<typename Packet_Type>
inline Packet_Type ParsingPacket(BYTE* buffer, int32 len)
{
	Packet_Type pkt;
	pkt.ParseFromArray(buffer + sizeof(Pkt_Header), len);

	return pkt;
}