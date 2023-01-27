#include "ServerNpc.h"

ServerNpc::~ServerNpc()
{
    delete mysql;
    delete packetManager; //내부 malloc free시킬 다른 방법 찾을 수 있으면 좋을 듯
}

void ServerNpc::Connect(boost::asio::ip::tcp::endpoint& endpoint)
{
	m_Socket.async_connect(endpoint, boost::bind(&ServerNpc::handle_connect, this, boost::asio::placeholders::error)
	);
}

void ServerNpc::PostWrite(LoginData loginData)
{
    boost::mutex::scoped_lock(mutex);
    if (m_Socket.is_open() == false)
    {
        return;
    }

    /*
    if (m_nSeqNumber > 7)
    {
        m_Socket.close();
        return;
    }
    */
    

    m_nSeqNumber += 1;
    outputBuf = packetManager->MakeLoginPacket(loginData);
    
    
    bufSize = packetManager->GetBufSize();
    m_WriteMessage = outputBuf;

    boost::asio::async_write(m_Socket, boost::asio::buffer(outputBuf, bufSize),
        boost::bind(&ServerNpc::handle_write, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );

    PostReceive();
}

void ServerNpc::PostWrite(GameData gameData)
{
    boost::mutex::scoped_lock(mutex);
    if (m_Socket.is_open() == false)
    {
        return;
    }

    /*
    if (m_nSeqNumber > 7)
    {
        m_Socket.close();
        return;
    }
    */


    m_nSeqNumber += 1;

    outputBuf = packetManager->MakeGamePacket(gameData);

    bufSize = packetManager->GetBufSize();
    m_WriteMessage = outputBuf;

    boost::asio::async_write(m_Socket, boost::asio::buffer(outputBuf, bufSize),
        boost::bind(&ServerNpc::handle_write, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );

}

void ServerNpc::PostReceive()
{
    memset(&m_ReceiveBuffer, '\0', sizeof(m_ReceiveBuffer));

    m_Socket.async_read_some(boost::asio::buffer(m_ReceiveBuffer),
        boost::bind(&ServerNpc::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred)
    );
}

void ServerNpc::handle_connect(const boost::system::error_code& error)
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

        PostReceive();
    }
}

void ServerNpc::handle_write(const boost::system::error_code& error, size_t bytes_transferred)
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
        //PostReceive();
    }
}

void ServerNpc::handle_receive(const boost::system::error_code& error, size_t bytes_transferred)
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
        inputBuf = &m_ReceiveBuffer[0];
        LoginData loginData;
        protobuf::io::ArrayInputStream input_array_stream(inputBuf, bytes_transferred);
        protobuf::io::CodedInputStream input_coded_stream(&input_array_stream);
        int matchRoom = packetManager->PacketProcess(&loginData, input_coded_stream);
        if (matchRoom != 0)
        {
            //cout << "LoginData: " << loginData.mapLevel << " / " << loginData.matchRoom << endl;
            PostWrite(loginData);
            //ObstacleThread* obsThread;
            //obsThread->loginData = loginData;
            //obsThread->npcServer = this;
            boost::thread* tempThread = new boost::thread(ObstacleThread(loginData, *this));
            //boost::thread* tempThread = new boost::thread(obsThread);
            threadGroup.push_back(make_pair(matchRoom, tempThread));
        }
        else
        {
            PostReceive();
        }
    }
}
