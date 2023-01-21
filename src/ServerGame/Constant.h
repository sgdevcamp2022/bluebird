#pragma once

#define THREAD_SIZE 10
#define ROOM_COUNT 20

struct Vector3
{
	float x;
	float y;
	float z;
};

template<typename Packet_Type, typename Header_Type>
inline Packet_Type ParsingPacket(BYTE* buffer, int32 len)
{
	Packet_Type pkt;
	pkt.ParseFromArray(buffer + sizeof(Header_Type), len);

	return pkt;
}