// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef SERVER_APPLICATIONSERVER_INCLUDE_IREQUESTHANDLER_HPP_
#define SERVER_APPLICATIONSERVER_INCLUDE_IREQUESTHANDLER_HPP_

#include <boost/asio/buffer.hpp>
#include <myprotocol.hpp>

class IRequestHandler {
 public:
  virtual ~IRequestHandler() = default;

  virtual void HandleRequest(MyProtocolPkg &request,
                             MyProtocolPkg &response) = 0;
};

#endif  // SERVER_APPLICATIONHANDLER_INCLUDE_IREQUESTHANDLER_HPP_
