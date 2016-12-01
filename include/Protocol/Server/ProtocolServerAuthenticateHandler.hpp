//
// Created by victor on 29/11/16.
//

#ifndef RTYPE_PROTOCOLSERVERAUTHENTICATEHANDLER_HPP
#define RTYPE_PROTOCOLSERVERAUTHENTICATEHANDLER_HPP

#include "Protocol/Server/IProtocolServerHandler.hpp"

class ProtocolServerAuthenticateHandler : public IProtocolServerHandler {
public:
    ~ProtocolServerAuthenticateHandler() {}

public:
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageServer const &) = 0;
    virtual void onGetLAUNCHPackage(LAUNCHPackageServer const &) {};
    virtual void onGetSTATUSPackage(STATUSPackageServer const &) {};
};

#endif //RTYPE_PROTOCOLSERVERAUTHENTICATEHANDLER_HPP
