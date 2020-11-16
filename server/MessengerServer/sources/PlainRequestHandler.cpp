// Copyright 2020 <Kam1runetz notsoserious2017@gmail.com>

#include <PlainRequestHandler.hpp>

void PlainRequestHandler::HandleRequest(MyProtocolPkg &request,
                                        MyProtocolPkg &response) {
  response = request;
}
