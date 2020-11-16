// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef SERVER_MESSENGERSERVER_INCLUDE_PLAINREQUESTHANDLER_HPP_
#define SERVER_MESSENGERSERVER_INCLUDE_PLAINREQUESTHANDLER_HPP_

#include <IRequestHandler.hpp>

class PlainRequestHandler : public IRequestHandler {
 public:
  void HandleRequest(MyProtocolPkg &request, MyProtocolPkg &response) override;
};

#endif  // SERVER_MESSENGERSERVER_INCLUDE_PLAINREQUESTHANDLER_HPP_
