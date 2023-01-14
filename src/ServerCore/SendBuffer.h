#pragma once

/*----------------
	SendBuffer
-----------------*/

class SendBuffer : enable_shared_from_this<SendBuffer>
{
public:
	SendBuffer(int32 bufferSize);
	~SendBuffer();

	BYTE*	Buffer() { return _buffer.data(); }
	int32	WriteSize() { return _write_size; }
	uint32	Capacity() { return static_cast<uint32>(_buffer.size()); }
	void	Close(uint32 write_size);

private:
	vector<BYTE>	_buffer;
	int32			_write_size = 0;
};

