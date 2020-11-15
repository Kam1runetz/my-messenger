//
// Created by w1ckedente on 15.11.2020.
//

#ifndef MESSENGER_PLAINREQUESTHANDLER_HPP
#define MESSENGER_PLAINREQUESTHANDLER_HPP

#include <IRequestHandler.hpp>

class PlainRequestHandler : public IRequestHandler {
public:
    MyProtocolPkg HandleRequest(MyProtocolPkg &request) override;
};

#endif //MESSENGER_PLAINREQUESTHANDLER_HPP
