// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#include <ConnectionManager.hpp>
#include <boost/bind.hpp>

void ConnectionManager::Start(std::shared_ptr<Connection> connection) {
  connections.insert(connection);
  connection->Start();
}

void ConnectionManager::Stop(std::shared_ptr<Connection> connection) {
  connections.erase(connection);
  connection->Stop();
}

void ConnectionManager::StopAll() {
  std::for_each(connections.begin(), connections.end(),
                boost::bind(&Connection::Stop, _1));
  connections.clear();
}
