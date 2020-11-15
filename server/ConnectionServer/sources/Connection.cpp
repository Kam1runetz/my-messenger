// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#include <Connection.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <ConnectionManager.hpp>

// todo: logging errors

Connection::Connection(boost::asio::io_service &ioService, ConnectionManager &manager,
                       std::shared_ptr<IRequestHandler> requestHandler) :
        socket(ioService),
        connectionManager(manager),
        requestHandler(requestHandler) {}

boost::asio::ip::tcp::socket &Connection::Socket() {
    return socket;
}

void Connection::Start() {
    socket.async_read_some(boost::asio::buffer(boost::asio::buffer(buffer)),
                           boost::bind(&Connection::handleRead, shared_from_this(),
                                       boost::asio::placeholders::error,
                                       boost::asio::placeholders::bytes_transferred));
}

void Connection::Stop() {
    socket.close();
}

void Connection::handleRead(const boost::system::error_code &err, std::size_t bytesTransferred) {
    if (!err) {
        if (bytesTransferred != sizeof(MyProtocolPkg)) return;
        MyProtocolPkg pkg = *(MyProtocolPkg *) (buffer.data());
        int requestHandlingError = requestHandler->HandleRequest(pkg, response);
        if (requestHandlingError) return;
        // todo response to buffer and async write
        void *responseBytes = nullptr;
        auto responseBuffer = boost::asio::buffer(responseBytes, sizeof(MyProtocolPkg));
        boost::asio::async_write(socket, responseBuffer,
                                 boost::bind(&Connection::handleWrite, shared_from_this(),
                                             boost::asio::placeholders::error));
    } else if (err != boost::asio::error::operation_aborted) {
        connectionManager.Stop(shared_from_this());
    } else {
        // todo logging
    }
}

void Connection::handleWrite(const boost::system::error_code &err) {
    if (!err) {
        boost::system::error_code ignoredErrCode;
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ignoredErrCode);
    } else if (err != boost::asio::error::operation_aborted) {
        connectionManager.Stop(shared_from_this());
    } else {
        // todo logging
    }
}


