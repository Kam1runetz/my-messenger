// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef SERVER_CONNECTIONSERVER_INCLUDE_SERVER_HPP_
#define SERVER_CONNECTIONSERVER_INCLUDE_SERVER_HPP_

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <myprotocol.hpp>
#include <myprotocoldefs.hpp>
#include <IRequestHandler.hpp>
#include <Connection.hpp>
#include <ConnectionManager.hpp>
#include <memory>

class Server : private boost::noncopyable {
public:
    explicit Server(const char address[], const char port[], IRequestHandler *requestHandler);

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

#endif // SERVER_CONNECTIONSERVER_INCLUDE_SERVER_HPP_
