// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef SERVER_CONNECTIONSERVER_INCLUDE_CONNECTIONMANAGER_HPP_
#define SERVER_CONNECTIONSERVER_INCLUDE_CONNECTIONMANAGER_HPP_

#include <Connection.hpp>
#include <boost/noncopyable.hpp>
#include <memory>
#include <set>

class ConnectionManager : private boost::noncopyable {
 public:
  void Start(std::shared_ptr<Connection> connection);
  void Stop(std::shared_ptr<Connection> connection);

  void StopAll();

 private:
  std::set<std::shared_ptr<Connection>> connections;
};

#endif  // SERVER_CONNECTIONSERVER_INCLUDE_CONNECTIONMANAGER_HPP_
