// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#include <Server.hpp>
#include <boost/bind.hpp>

Server::Server(const char *address, const char *port,
               IRequestHandler *aRequestHandler)
    : ioService(),
      acceptor(ioService),
      connectionManager(),
      requestHandler(aRequestHandler),
      newConnection(
          new Connection(ioService, connectionManager, requestHandler)) {
  boost::asio::ip::tcp::resolver resolver(ioService);
  boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(),
                                              address, port);
  boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);

  acceptor.open(endpoint.protocol());
  acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
  acceptor.bind(endpoint);
  acceptor.listen();
  acceptor.async_accept(newConnection->Socket(),
                        boost::bind(&Server::handleAccept, this,
                                    boost::asio::placeholders::error));
}

void Server::Run() { ioService.run(); }

void Server::Stop() { ioService.post(boost::bind(&Server::handleStop, this)); }

void Server::handleAccept(const boost::system::error_code &e) {
  if (!e) {
    connectionManager.Start(newConnection);
    newConnection.reset(
        new Connection(ioService, connectionManager, requestHandler));
    acceptor.async_accept(newConnection->Socket(),
                          boost::bind(&Server::handleAccept, this,
                                      boost::asio::placeholders::error));
  }
}

void Server::handleStop() {
  acceptor.close();
  connectionManager.StopAll();
}
