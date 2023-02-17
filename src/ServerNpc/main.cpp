#include "ServerNpc.h"

int main(int argc, char* argv[])
{
    boost::asio::io_context io_service;
    //203.241.228.47
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("203.241.228.47"), 4000);
    ServerNpc client(io_service);
    client.Connect(endpoint);
    io_service.run();
    cout << "匙飘况农 立加 辆丰" << endl;
    getchar();

    return 0;
}