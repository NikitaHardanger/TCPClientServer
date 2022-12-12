//
// Created by Nikit on 11/11/2022.
//

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <queue>


namespace TCP {
    using boost::asio::ip::tcp;
    namespace io = boost::asio;

    using messageHandler = std::function<void(std::string)>;
    using errorHandler = std::function<void()>; // Handler error
class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
    public:
        using pointer = std::shared_ptr<TCPConnection>;

        static pointer Create(io::ip::tcp::socket&& socket) {
            return pointer(new TCPConnection(std::move(socket)));
        }

        inline const std::string& geUserName() const { return _username;}
        tcp::socket& socket() {
            return _socket;
        }

        void Start(messageHandler&&messageHandler, errorHandler&& errorHandler);
        void Post(const std::string& message);

    private:
        explicit TCPConnection(io::ip::tcp::socket&& socket);

        // Wait for a new message from client
        void asyncRead();
        void onRead(boost::system::error_code ec, size_t bytesTransferred);

        void asyncWrite();
        void onWrite(boost::system::error_code ec, size_t bytesTransferred);

    private:
        tcp::socket _socket;
        std::string _username;

        std::queue<std::string> _outGoingMessages;
        io::streambuf _streamBuf {65536};

        messageHandler _messageHandler;
        errorHandler _errorHandler;
    };
}

