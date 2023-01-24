#include "NpcServer.h"
//8001을 메인, 8000을 쓰레드
NpcServer::~NpcServer()
{
    delete mysql;
    delete packetManager; //내부 malloc free시킬 다른 방법 찾을 수 있으면 좋을 듯
}

void NpcServer::Connect(boost::asio::ip::tcp::endpoint& endpoint)
{
	m_Socket.async_connect(endpoint, boost::bind(&NpcServer::handle_connect, this, boost::asio::placeholders::error)
	);
}

void NpcServer::PostWrite()
{
    if (m_Socket.is_open() == false)
    {
        return;
    }

    
    if (m_nSeqNumber > 7)
    {
        m_Socket.close();
        return;
    }
    
    

    m_nSeqNumber += 1;
    //char* outputBuf;
    if (m_nSeqNumber == 1)
    {
        outputBuf = packetManager->MakePacket(atoi(res[0]), atoi(res[1]), atoi(res[2]), atoi(res[3]));
        temp[0] = atoi(res[0]);
        temp[1] = atoi(res[1]);
        temp[2] = atoi(res[2]);
        temp[3] = atoi(res[3]);
        //temp[3] = atoi(res[3]);
    }
    else
    {
        temp[0] += 1;
        outputBuf = packetManager->MakePacket(temp[0], temp[1], temp[2], temp[3]);
    }
    
    bufSize = packetManager->GetBufSize();
    //string str = outputBuf;
    //char szMessage[128] = { 0, };
    //sprintf_s(szMessage, 128 - 1, "%d - Send Message", m_nSeqNumber);
    m_WriteMessage = outputBuf;

    boost::asio::async_write(m_Socket, boost::asio::buffer(outputBuf, bufSize),
        boost::bind(&NpcServer::handle_write, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );

    PostReceive();
}

void NpcServer::PostReceive()
{
    memset(&m_ReceiveBuffer, '\0', sizeof(m_ReceiveBuffer));

    m_Socket.async_read_some(boost::asio::buffer(m_ReceiveBuffer),
        boost::bind(&NpcServer::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
}

void NpcServer::handle_connect(const boost::system::error_code& error)
{
    if (error)
    {
        cout << "connect failed : " << error.message() << endl;
    }
    else
    {
        cout << "connected" << endl;

        mysql = new ConnectToSQL();
        //res = mysql->SQLQuery("select * from objectinfo");
        //cout << res[0] << " / " << res[1] << " / " << res[2] << " / " << res[3] << endl;
        packetManager = new PacketManager;

        //PostWrite();
        PostReceive();
    }
}

void NpcServer::handle_write(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (error)
    {
        if (error == boost::asio::error::eof)
        {
            cout << "서버와 연결이 끊어졌습니다." << endl;
        }
        else
        {
            cout << "error No: " << error.value() << " error Message: " << error.message() << endl;
        }
    }
    else
    {
        cout << m_nSeqNumber << " 전송 완료" << endl;
        //PostWrite();
    }
}

//Thread Test Class
class ThreadTest
{
public:
    ThreadTest() {}
    void operator()()
    {
        while (true)
        {
            cout << "Thread " << boost::this_thread::get_id() << endl;
            boost::this_thread::sleep(boost::posix_time::seconds(1));
        }

    }
};
//

void NpcServer::handle_receive(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (error)
    {
        if (error == boost::asio::error::eof)
        {
            cout << "서버와 연결이 끊어졌습니다." << endl;
        }
        else
        {
            cout << "error No: " << error.value() << " error Message: " << error.message() << endl;
        }
    }
    else
    {
        //outputBuf = &m_ReceiveBuffer[0];
        inputBuf = &m_ReceiveBuffer[0];
        protobuf::io::ArrayInputStream input_array_stream(inputBuf, bytes_transferred);
        protobuf::io::CodedInputStream input_coded_stream(&input_array_stream);
        int matchRoom = packetManager->PacketProcess(input_coded_stream);
        if (matchRoom != 0)
        {
            boost::thread* tempThread = new boost::thread(ThreadTest());
            threadGroup.push_back(make_pair(matchRoom, tempThread));
        }
        //const string strRecvMessage = m_ReceiveBuffer.data();
        //cout << "서버에서 받은 메시지: " << strRecvMessage << ", 받은 크기: " << bytes_transferred << endl;
        //PostWrite();
        PostReceive();
    }
}

void NpcServer::Map01Thread()
{
    try
    {
        while (true)
        {
            cout << "1" << endl;
            boost::this_thread::sleep(boost::posix_time::millisec(500));
        }
    }
    catch (boost::thread_interrupted&)
    {
        cout << "Map01Thread Interrupted" << endl;
    }
}

int main(int argc, char* argv[])
{
    boost::asio::io_context io_service;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 8000);
    NpcServer client(io_service);
    client.Connect(endpoint);
    io_service.run();
    cout << "네트워크 접속 종료" << endl;
    getchar();
    
    return 0;
}