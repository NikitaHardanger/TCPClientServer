//
// Created by Nikit on 11/11/2022.
//

#include "TCPNetworking/server/tcp_connection.h"
#include <iostream>


namespace TCP {
    TCPConnection::TCPConnection(io::ip::tcp::socket&& socket) : _socket(std::move(socket)) {
        boost::system::error_code ec;
        std::stringstream name;
        name << _socket.remote_endpoint();

        _username = name.str();
    }

    void TCPConnection::Start(messageHandler&&messageHandler, errorHandler&& errorHandler) {
        _messageHandler = std::move(messageHandler);
        _errorHandler = std::move(errorHandler);
        asyncRead();
    }

    void TCPConnection::Post(const std::string &message) {
        bool queueIdle = _outGoingMessages.empty();
        _outGoingMessages.push(message);

        if (queueIdle) {
            asyncWrite();
        }
    }

    void TCPConnection::asyncRead() {
        io::async_read_until(_socket, _streamBuf, "\n", [self = shared_from_this()]
        (boost::system::error_code ec, size_t bytesTransferred) {
            self->onRead(ec, bytesTransferred);
        });
    }

    void TCPConnection::onRead(boost::system::error_code ec, size_t bytesTransferred) {
        if (ec) {
            _socket.close(ec);

            _errorHandler();
            return;
        }

        std::stringstream message;
        message << _username << ": " << std::istream(&_streamBuf).rdbuf();
        _streamBuf.consume((bytesTransferred));

        _messageHandler(message.str());
        asyncRead();
    }

    void TCPConnection::asyncWrite() {
        io::async_write(_socket, io::buffer(_outGoingMessages.front()), [self = shared_from_this()]
                (boost::system::error_code ec, size_t bytesTransferred) {
            self->onWrite(ec, bytesTransferred);
        });
    }

    void TCPConnection::onWrite(boost::system::error_code ec, size_t bytesTransferred) {
        if (ec) {
            _socket.close(ec);

            _errorHandler();
            return;
        }

        _outGoingMessages.pop();

        if (!_outGoingMessages.empty()) {
            asyncWrite();
        }
    }
}
