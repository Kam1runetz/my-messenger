// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef SERVER_CONNECTIONSERVER_INCLUDE_SERVER_HPP_
#define SERVER_CONNECTIONSERVER_INCLUDE_SERVER_HPP_

#include <Connection.hpp>
#include <ConnectionManager.hpp>
#include <IRequestHandler.hpp>
#include <boost/asio.hpp>
#include <memory>

class Server {
 public:
  explicit Server(const char address[], const char port[],
                  IRequestHandler *requestHandler);

  Server(const Server &) = delete;
  Server &operator=(const Server &) = delete;

  ~Server() = default;

  void Run();

  void Stop();

 private:
  void handleAccept(const boost::system::error_code &e);

  void handleStop();

  boost::asio::io_service ioService;
  boost::asio::ip::tcp::acceptor acceptor;

  ConnectionManager connectionManager;
  std::shared_ptr<IRequestHandler> requestHandler;
  std::shared_ptr<Connection> newConnection;
};

#endif  // SERVER_CONNECTIONSERVER_INCLUDE_SERVER_HPP_
