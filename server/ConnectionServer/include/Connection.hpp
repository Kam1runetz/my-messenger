// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef SERVER_CONNECTIONSERVER_INCLUDE_CONNECTION_HPP_
#define SERVER_CONNECTIONSERVER_INCLUDE_CONNECTION_HPP_

#include <ServersMiddleware.hpp>
#include <array>
#include <boost/asio.hpp>
#include <memory>

class ConnectionManager;

class Connection : public std::enable_shared_from_this<Connection> {
 public:
  explicit Connection(boost::asio::io_service &ioService,
                      ConnectionManager &manager,
                      const std::shared_ptr<ServersMiddleware> &aMiddleware);
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
  std::shared_ptr<ServersMiddleware> middleware;
  std::array<std::uint8_t, ServersMiddleware::PackageSize> buffer;
};

#endif  // SERVER_CONNECTIONSERVER_INCLUDE_CONNECTION_HPP_
