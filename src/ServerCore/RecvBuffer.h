#pragma once
class RecvBuffer
{
	enum { BUFFER_COUNT = 10 };
public:
	RecvBuffer(int32 bufferSize);
	~RecvBuffer();

	void Clean();
	bool OnRead(int32 num_of_bytes);
	bool OnWrite(int32 num_of_bytes);

	BYTE* Read_pos() { return &_buffer[_read_pos]; }
	BYTE* Write_pos() { return &_buffer[_write_pos]; }
	int32 Data_size() { return _write_pos - _read_pos; }
	int32 Free_size() { return _capacity - _write_pos; }

private:
	int32			_capacity = 0;
	int32			_buffer_size = 0;
	int32			_read_pos = 0;
	int32			_write_pos = 0;
	vector<BYTE>	_buffer;
};

