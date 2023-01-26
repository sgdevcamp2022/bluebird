using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Google.Protobuf.Protocol;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System;
using System.Threading;
using Google.Protobuf;
using System.Runtime.InteropServices;
using System.Drawing;
using System.Diagnostics;

public class Networking : MonoBehaviour
{
    //private TcpClient socketConnection;
    //private Socket socket;
    private TcpClient socket;
    private Thread clientReceiveThread;

    //서버 IP 및 포트번호
    static private string mIp = "127.0.0.1";
    static private IPAddress ipAddress = IPAddress.Parse(mIp);
    static private int mPort = 5000;

    
    IPEndPoint endPoint = new IPEndPoint(ipAddress, mPort);



    //종단점 (서버종단점 연결용)
    private IPEndPoint mIpEndPoint;
   

    public void Start()
    {
        ConnectToTcpServer();
    }



    private void ConnectToTcpServer()
    {
        try
        {

            clientReceiveThread = new Thread(new ThreadStart(ListenForData));
            //스레드가 배경 스레드인지를 나타내는 값을 가져오거나 설정, true가 백그라운드 스레드로 돌리겠다
            //메인 스레드가 종료되면 백그라운드 스레드도 종료됨. 그러나 포그라운드 스레드는 메인 스레드가 종료돼도 작동
            clientReceiveThread.IsBackground = true;
            clientReceiveThread.Start();
        }
        catch (Exception e)
        {
            UnityEngine.Debug.Log("On Client connection exception " + e);
        }
    }

    public void ListenForData()
    {
        try
        {
            //ip 주소와 port를 지정하여 자동으로 TCP 연결 
            socket = new TcpClient(mIp, mPort);
           

            UnityEngine.Debug.Log("Connected...");
            byte[] bytes = new byte[1024];
            

            while (true)
            {
                //using문을 사용하면 리소스의 범위를 벗어나면 자동으로 dispose하여 관리를 쉽게 도와줌.
                //getstream 메서드는 tcp 네트워크 스트림을 리턴, 이 네트워크 스트림을 이용해 네트워크로 데이터 송수신

                using (NetworkStream stream = socket.GetStream())
                {
                    int len;


                    //read 메소드를 통해 서버에서 바이트 데이터를 읽어온다.
                    while ((len = stream.Read(bytes, 0, bytes.Length)) != 0)
                    {
                        UnityEngine.Debug.Log("something came");
                        //byte[] incommingdata = new byte[len];

                        //PacketHandler.HandlerPacket<Pkt_Head>(incommingdata,len);
                        //Array.Copy(bytes, 0, incommingdata, 0, len);

                        //string servermessage = Encoding.ASCII.GetString(incommingdata);
                        //UnityEngine.Debug.Log("server message: " + test);



                    }


                }
            }

        }
        catch (SocketException socketException)
        {
            UnityEngine.Debug.Log("Socket Exception " + socketException);
        }
    }

    public void SendMessage()
    {
        //소켓 연결이 안된 상태
        if (!socket.Connected)
            return;
        try
        {
            if (socket.Connected)
            {
                NetworkStream stream = socket.GetStream();
                if (stream.CanWrite)
                {

                    Data dataPkt = new Data()
                    {
                        Id = 1,
                        MapLevel = 2,
                        MatchRoom = 0,
                        //Plyaer = {new Player {X = 0,Y=0,Z=0 } }

                    };
                  

                    byte[] datas = PacketHandler.Make_login_handler(dataPkt, INGAME.Connect);

                    //바이트 배열을 넣어 전송
                    stream.Write(datas);
                    UnityEngine.Debug.Log("Client Sent Map Join Message");
                }
            }
        }
        catch (SocketException socketException)
        {
            UnityEngine.Debug.Log("SendMessage Exception: " + socketException);
        }
    }

    public void SendPlayerMessage()
    {
        //소켓 연결이 안된 상태
        if (!socket.Connected)
            return;
        try
        {
            NetworkStream stream = socket.GetStream();
            if (stream.CanWrite)
            {

                Data dataPkt = new Data()
                {
                    Id = 1,
                    MapLevel = 2,
                    MatchRoom = 0,
                    Plyaer = { new Player { X = 0.0f, Y = 0.0f, Z = 0.0f } }

                };

                byte[] datas = PacketHandler.Make_login_handler(dataPkt, INGAME.Move);

                //바이트 배열을 넣어 전송
                stream.Write(datas);
                UnityEngine.Debug.Log("Client Sent Player Message");
            }
        }
        catch (SocketException socketException)
        {
            UnityEngine.Debug.Log("Socket exception: " + socketException);
        }
    }
    /*
    public void SendMessage(float x,float y,float z)
    {
        //소켓 연결이 안된 상태
        if (socket == null)
            return;
        try
        {
            NetworkStream stream = socket.GetStream();
            if (stream.CanWrite)
            {

                Player pkt = new Data()
                {
                    
                };

                byte[] datas = PacketHandler.Make_login_handler(pkt);

                //바이트 배열을 넣어 전송
                stream.Write(datas);
                UnityEngine.Debug.Log("Client Sent Map Join Message");
            }
        }
        catch (SocketException socketException)
        {
            UnityEngine.Debug.Log("Socket exception: " + socketException);
        }
    }




    public bool CheckConnection()
    {
        if (isConnected)
            return true;
        else
            return false;
    }


   
    public void SendPlayerMessage(float x,float y,float z)
    {
        if (!isConnected)
        {
            return;
        }
        try
        {
            if (isConnected)
            {
                int len = 0;
                Player pkt = new Player()
                {
                    X = x,
                    Y = y,
                    Z = z
                
                };

                byte[] datas = PacketHandler.Make_login_handler(pkt);

                //바이트 배열을 넣어 전송
                len = socket.Send(datas);
                Debug.Log(len + " : Success Send");

                //S_TEST pkt2 = new S_TEST();
                //pkt2.MergeFrom(datas);

                //data = reader.ReadLine();
                //Debug.Log(data);
            }
        }
        catch (SocketException socketException)
        {
            Debug.Log("Socket exception: " + socketException);
        }
    }
    
public void ReceiveMessage()
{
    if (isConnected)
    {
        try
        {
            byte[] data;
            data = new Byte[256];
            String receivedData = String.Empty;

            int bytes = socket.Receive(data);
            receivedData = Encoding.ASCII.GetString(data, 0, bytes);

            Debug.Log("Received Message from Server"  + receivedData + "길이" + bytes);
        }
        catch (Exception e)
        {
            Debug.Log("Receive Message Error " + e);
        }
    }
}


/// Send message to server using socket connection. 	
public void SendMessage()
{
    if (!isConnected)
    {
        return;
    }
    try
    {
        if (isConnected)
        {
            int len = 0;
            Data pkt = new Data()
            {
                Id = 1,
                MapLevel = 100,
                MatchRoom = 10
            };

            byte[] datas = PacketHandler.Make_login_handler(pkt);

            //바이트 배열을 넣어 전송
            len = socket.Send(datas);
            Debug.Log(len + " : Success Send");

            //S_TEST pkt2 = new S_TEST();
            //pkt2.MergeFrom(datas);

            //data = reader.ReadLine();
            //Debug.Log(data);
        }
    }
    catch (SocketException socketException)
    {
        Debug.Log("Socket exception: " + socketException);
    }
}
*/
}
