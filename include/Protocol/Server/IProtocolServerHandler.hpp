//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_IPROTOCOLSERVERHANDLER_HPP
#define RTYPE_IPROTOCOLSERVERHANDLER_HPP

#include "ProtocolServerPackage.hpp"

class IProtocolServerHandler {
public:
    virtual ~IProtocolServerHandler() {}

public:
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageServer const &) = 0;
    virtual void onGetLAUNCHPackage(LAUNCHPackageServer const &) = 0;
    virtual void onGetSTATUSPackage(STATUSPackageServer const &) = 0;
};

#endif //RTYPE_IPROTOCOLROOMHANDLER_HPP
