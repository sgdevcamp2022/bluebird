#include "pch.h"
#include "RecvBuffer.h"

RecvBuffer::RecvBuffer(int32 bufferSize) : _buffer_size(bufferSize)
{
	_capacity = bufferSize * BUFFER_COUNT;
	_buffer.resize(_capacity);
}

RecvBuffer::~RecvBuffer()
{

}

void RecvBuffer::Clean()
{
	int32 data_size = Data_size();
	if (data_size == 0)
	{
		_read_pos = _write_pos = 0;
	}
	else {
		if (Free_size() < _buffer_size) {
			::memcpy(&_buffer[0], &_buffer[_read_pos], data_size);
			_read_pos = 0;
			_write_pos = data_size;
		}
	}
}

bool RecvBuffer::OnRead(int32 num_of_bytes)
{
	if (num_of_bytes > Data_size())
		return false;

	_read_pos += num_of_bytes;
	return true;
}

bool RecvBuffer::OnWrite(int32 num_of_bytes)
{
	if (num_of_bytes > Free_size())
		return false;

	_write_pos += num_of_bytes;
	return true;
}
