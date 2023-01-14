#include "pch.h"
#include "SendBuffer.h"

/*----------------
	SendBuffer
-----------------*/

SendBuffer::SendBuffer(int32 bufferSize)
{
	_buffer.resize(bufferSize);
}

SendBuffer::~SendBuffer()
{

}

void SendBuffer::Close(uint32 write_size) {
	if (write_size > Capacity())
		return;
	_write_size = write_size;
}