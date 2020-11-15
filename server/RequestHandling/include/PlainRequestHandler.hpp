// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef SERVER_REQUESTHANDLING_INCLUDE_PLAINREQUESTHANDLER_HPP_
#define SERVER_REQUESTHANDLING_INCLUDE_PLAINREQUESTHANDLER_HPP_

#include <IRequestHandler.hpp>

class PlainRequestHandler : public IRequestHandler {
public:
    MyProtocolPkg HandleRequest(MyProtocolPkg &request) override;
};

#endif // SERVER_REQUESTHANDLING_INCLUDE_PLAINREQUESTHANDLER_HPP_
