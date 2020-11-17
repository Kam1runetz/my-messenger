//
// Created by w1ckedente on 17.11.2020.
//

#ifndef MESSENGER_APPLICATIONSERVER_HPP
#define MESSENGER_APPLICATIONSERVER_HPP

#include <myprotocol.hpp>

class ApplicationServer {
 public:
  ApplicationServer() = default;
  ~ApplicationServer() = default;

  void HandleRequest(MyProtocolPkg &request, MyProtocolPkg &response);
};

#endif  // MESSENGER_APPLICATIONSERVER_HPP
