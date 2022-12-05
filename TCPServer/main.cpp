
#include <iostream>
#include <boost/asio.hpp>
#include "TCPNetworking/tcp_server.h"


using boost::asio::ip::tcp;


int main(int argc, char* argv[]) {

        TCP::TCPServer server {TCP::IPV::V4, 1337};

        server.Run();

    return 0;
}



