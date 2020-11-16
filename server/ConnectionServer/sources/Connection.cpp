// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#include <Connection.hpp>
#include <ConnectionManager.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
// todo delete this
#include <iostream>

// todo: logging errors

Connection::Connection(boost::asio::io_service &ioService,
                       ConnectionManager &manager,
                       std::shared_ptr<IRequestHandler> requestHandler)
    : socket(ioService),
      connectionManager(manager),
      requestHandler(requestHandler) {}

boost::asio::ip::tcp::socket &Connection::Socket() { return socket; }

void Connection::Start() {
  socket.async_read_some(
      boost::asio::buffer(boost::asio::buffer(buffer)),
      boost::bind(&Connection::handleRead, shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}

void Connection::Stop() {
  // todo debug
  std::cout << "Connection closed" << std::endl;
  socket.close();
}

void Connection::handleRead(const boost::system::error_code &err,
                            std::size_t bytesTransferred) {
  if (!err) {
    if (bytesTransferred != sizeof(MyProtocolPkg)) return;
    MyProtocolPkg pkg = *reinterpret_cast<MyProtocolPkg *>(buffer.data());
    // todo debug
    std::cout << "New message: " << pkg.Content.messagePkg.Message << std::endl;
    int requestHandlingError = requestHandler->HandleRequest(pkg, response);
    // todo
    // if (requestHandlingError == ErrCloseConnection) {
    //   connectionManager.Stop(shared_from_this())
    //   return;
    // }
    if (requestHandlingError) return;
    boost::asio::async_write(
        socket, boost::asio::buffer(&response, sizeof(MyProtocolPkg)),
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
    Start();
  } else if (err != boost::asio::error::operation_aborted) {
    connectionManager.Stop(shared_from_this());
  } else {
    // todo logging
  }
}
