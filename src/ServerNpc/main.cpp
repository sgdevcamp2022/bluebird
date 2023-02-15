#include "ServerNpc.h"

int main(int argc, char* argv[])
{
    boost::asio::io_context io_service;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 4000);
    ServerNpc client(io_service);
    client.Connect(endpoint);
    io_service.run();
    cout << "匙飘况农 立加 辆丰" << endl;
    getchar();

    return 0;
}