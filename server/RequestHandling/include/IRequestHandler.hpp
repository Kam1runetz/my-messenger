// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#ifndef SERVER_REQUESTHANDLING_INCLUDE_IREQUESTHANDLER_HPP_
#define SERVER_REQUESTHANDLING_INCLUDE_IREQUESTHANDLER_HPP_

#include <myprotocol.hpp>

class IRequestHandler {
public:
    virtual ~IRequestHandler() = default;
    virtual MyProtocolPkg HandleRequest(MyProtocolPkg &request) = 0;
};

#endif // SERVER_REQUESTHANDLING_INCLUDE_IREQUESTHANDLER_HPP_
