//
// Created by w1ckedente on 15.11.2020.
//

#ifndef MESSENGER_IREQUESTHANDLER_HPP
#define MESSENGER_IREQUESTHANDLER_HPP

#include <myprotocol.hpp>

class IRequestHandler {
public:
    virtual ~IRequestHandler() = default;
    virtual MyProtocolPkg HandleRequest(MyProtocolPkg &request) = 0;
};

#endif //MESSENGER_IREQUESTHANDLER_HPP
