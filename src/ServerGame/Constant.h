#pragma once

#define THREAD_SIZE 10
#define ROOM_COUNT 20
#define START_COUNT 2
#define WINNER1(count)	count/3
#define WINNER2(count)	WINNER1(count)/5
#define WINNER3	1

struct Vector3
{
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3(Protocol::Obtacle data) : x(data.x()), y(data.y()), z(data.z()) {}
	Vector3(Protocol::Player data) : x(data.x()), y(data.y()), z(data.z()) {}
	Vector3(Npc::Obstacle data) : x(data.x()), y(data.y()), z(data.z()) {}
	
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

template<typename T, typename Header, typename S>
inline SendBufferRef _MakeSendBuffer(T& pkt, S type)
{
	const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
	const uint16 packetSize = dataSize + sizeof(Header);

	SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
	Header* header = reinterpret_cast<Header*>(sendBuffer->Buffer());
	header->size = dataSize;
	header->type = type;
	cout << dataSize << " " << packetSize << endl;
	ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
	sendBuffer->Close(packetSize);

	return sendBuffer;
}