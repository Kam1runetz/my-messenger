// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef CLIENT_INCLUDE_ECHOCLIENT_HPP_
#define CLIENT_INCLUDE_ECHOCLIENT_HPP_

#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <myprotocol.hpp>
#include <myprotocoldefs.hpp>
#include <string>

// todo create client

class Client : private boost::noncopyable {
 public:
  Client() = default;
  ~Client() = default;

 private:
  boost::asio::ip::tcp::socket socket;
  boost::asio::ip::tcp::resolver resolver;
};

#endif  // CLIENT_INCLUDE_ECHOCLIENT_HPP_
