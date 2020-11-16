// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef SERVER_CONNECTIONSERVER_INCLUDE_CONNECTION_HPP_
#define SERVER_CONNECTIONSERVER_INCLUDE_CONNECTION_HPP_

#include <IRequestHandler.hpp>
#include <array>
#include <boost/asio.hpp>
#include <memory>
#include <myprotocol.hpp>

class ConnectionManager;

class Connection : public std::enable_shared_from_this<Connection> {
 public:
  explicit Connection(boost::asio::io_service &ioService,
                      ConnectionManager &manager,
                      std::shared_ptr<IRequestHandler> requestHandler);
  Connection(const Connection &) = delete;
  Connection &operator=(const Connection &) = delete;

  boost::asio::ip::tcp::socket &Socket();

  void Start();

  void Stop();

 private:
  void handleRead(const boost::system::error_code &err,
                  std::size_t bytesTransferred);

  void handleWrite(const boost::system::error_code &err);

  boost::asio::ip::tcp::socket socket;
  ConnectionManager &connectionManager;
  std::shared_ptr<IRequestHandler> requestHandler;
  std::array<std::uint8_t, sizeof(MyProtocolPkg)> buffer;
  MyProtocolPkg response;
};

#endif  // SERVER_CONNECTIONSERVER_INCLUDE_CONNECTION_HPP_
