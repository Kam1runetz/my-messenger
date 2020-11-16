// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef SERVER_REQUESTHANDLING_INCLUDE_IREQUESTHANDLER_HPP_
#define SERVER_REQUESTHANDLING_INCLUDE_IREQUESTHANDLER_HPP_

#include <boost/asio/buffer.hpp>
#include <myprotocol.hpp>

class IRequestHandler {
 public:
  virtual ~IRequestHandler() = default;

  [[nodiscard]] virtual int HandleRequest(MyProtocolPkg &request,
                                          MyProtocolPkg &response) = 0;
  static void *PkgToBytes(MyProtocolPkg &pkg) {
    void *bytes = new std::uint8_t[sizeof(pkg)];
    return bytes;
  }
};

#endif  // SERVER_REQUESTHANDLING_INCLUDE_IREQUESTHANDLER_HPP_
