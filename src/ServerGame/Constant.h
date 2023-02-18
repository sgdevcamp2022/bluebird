#pragma once

#define THREAD_SIZE 5
#define ROOM_COUNT 20

#define MAX_STAGE 3

inline bool Last_Stage(int stage) { return (stage == MAX_STAGE) ? true : false; }
inline int Solo_Goal(int stage) { return (stage == 1) ? 2 : 1; }
inline int Solo_Start(int stage) { return (stage == 1) ? 3 : 2; }

#define CLIENT_TEST true
#define NPC_TEST false

struct Vector3
{
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vector3(const Protocol::Vector& data) : x(data.x()), y(data.y()), z(data.z()) {}
	Vector3(const Npc::Vector3& data) : x(data.x()), y(data.y()), z(data.z()) {}

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
	ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
	sendBuffer->Close(packetSize);

	return sendBuffer;
}