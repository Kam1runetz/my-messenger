// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#include <Connection.hpp>
#include <ConnectionManager.hpp>
#include <ServersMiddleware.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <memory>

Connection::Connection(boost::asio::io_service &ioService,
                       ConnectionManager &manager,
                       const std::shared_ptr<ServersMiddleware> &aMiddleware)
    : socket(ioService),
      connectionManager(manager),
      middleware(aMiddleware),
      buffer() {}

boost::asio::ip::tcp::socket &Connection::Socket() { return socket; }

void Connection::Start() {
  socket.async_read_some(
      boost::asio::buffer(boost::asio::buffer(buffer)),
      boost::bind(&Connection::handleRead, shared_from_this(),
                  boost::asio::placeholders::error,
                  boost::asio::placeholders::bytes_transferred));
}

void Connection::Stop() { socket.close(); }

void Connection::handleRead(const boost::system::error_code &err,
                            std::size_t bytesTransferred) {
  if (!err) {
    if (bytesTransferred != ServersMiddleware::PackageSize) return;
    auto toSendBuffer = middleware->ProcessData(buffer);
    boost::asio::async_write(
        socket, toSendBuffer,
        boost::bind(&Connection::handleWrite, shared_from_this(),
                    boost::asio::placeholders::error));
  } else if (err != boost::asio::error::operation_aborted) {
    connectionManager.Stop(shared_from_this());
  }
}

void Connection::handleWrite(const boost::system::error_code &err) {
  if (!err) {
    Start();
  } else if (err != boost::asio::error::operation_aborted) {
    connectionManager.Stop(shared_from_this());
  }
}
