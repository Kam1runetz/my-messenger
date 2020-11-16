// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef SERVER_CONNECTIONSERVER_INCLUDE_CONNECTIONMANAGER_HPP_
#define SERVER_CONNECTIONSERVER_INCLUDE_CONNECTIONMANAGER_HPP_

#include <Connection.hpp>
#include <memory>
#include <set>

class ConnectionManager {
 public:
  ConnectionManager() = default;
  ConnectionManager(const ConnectionManager &) = delete;
  ConnectionManager &operator=(const ConnectionManager &) = delete;
  void Start(std::shared_ptr<Connection> connection);
  void Stop(std::shared_ptr<Connection> connection);

  void StopAll();

 private:
  std::set<std::shared_ptr<Connection>> connections;
};

#endif  // SERVER_CONNECTIONSERVER_INCLUDE_CONNECTIONMANAGER_HPP_
