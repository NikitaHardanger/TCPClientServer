
#include <iostream>
#include <boost/asio.hpp>
#include "TCPNetworking/server/tcp_server.h"


using boost::asio::ip::tcp;


int main(int argc, char* argv[]) {

    TCP::TCPServer server {TCP::IPV::V4, 1337};

    server.onJoin = [](TCP::TCPConnection::pointer server) {
        std::cout << "User has joined the server: " << server->geUserName() << std::endl;
    };

    server.onLeave = [](TCP::TCPConnection::pointer server) {
        std::cout << "User has left the server: " << server->geUserName() << std::endl;
    };

    server.onClientMessage = [&server](const std::string& message) {
        // Parse the message

        // Send message to client
        server.Broadcast(message);
    };
    server.Run();

    return 0;
}



