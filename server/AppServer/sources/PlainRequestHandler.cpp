// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#include <PlainRequestHandler.hpp>

int PlainRequestHandler::HandleRequest(MyProtocolPkg &request,
                                       MyProtocolPkg &response) {
  response = request;
  return 0;
}
