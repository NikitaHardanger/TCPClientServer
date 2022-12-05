//
// Created by Nikit on 11/11/2022.
//

#include <string>
#include <boost/asio.hpp>
#include <vector>
#include "TCPNetworking/tcp_connection.h"
#include <functional>


namespace TCP {
    enum class IPV {
        V4,
        V6
    };

    class TCPServer {
    public:
        TCPServer(IPV ipv, int port);

        int Run();

        template <typename T>
        void WriteToConnection(int connectionIndex, const T& message);

        template <typename T>
        using ListenCallBack = std::function<void(int, const T&)>;
        template <typename T>
        void RegisterListenCallBack(ListenCallBack<T> callback);
    private:
        void startAccept();

    private:
        IPV _ipVersion;
        int _port;

        boost::asio::io_context _ioContext;
        boost::asio::ip::tcp::acceptor _acceptor;

        std::vector<TCPConnection::pointer> _connections {};

    };
}


