//
// Created by Nikit on 11/11/2022.
//

#include <string>
#include <boost/asio.hpp>
#include <vector>
#include "tcp_connection.h"
#include <functional>
#include <optional>
#include <unordered_set>


namespace TCP {
    namespace io = boost::asio;

    enum class IPV {
        V4,
        V6
    };

    class TCPServer {
        using onJoinHandler = std::function<void(TCPConnection::pointer)>;
        using onLeaveHandler = std::function<void(TCPConnection::pointer)>;
        using onClientMessageHandler = std::function<void(std::string)>;

    public:
        TCPServer(IPV ipv, int port);

        int Run();

         void Broadcast(const std::string& message);
    private:
        void startAccept();

    public:
        onJoinHandler onJoin;
        onLeaveHandler onLeave;
        onClientMessageHandler onClientMessage;

    private:
        IPV _ipVersion;
        int _port;

        io::io_context _ioContext;
        io::ip::tcp::acceptor _acceptor;
        std::optional<io::ip::tcp::socket> _socket;
        std::unordered_set<TCPConnection::pointer> _connections {};

    };
}


