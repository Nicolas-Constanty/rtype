//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_IPROTOCOLGAMEHANDLER_HPP
#define RTYPE_IPROTOCOLGAMEHANDLER_HPP

#include "ProtocolGamePackage.hpp"

class IProtocolGameHandler {
public:
    virtual ~IProtocolGameHandler() {}

public:
    virtual void onGetPINGPackage(PINGPackageGame const &) = 0;
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageGame const &) = 0;
    virtual void onGetCREATEPackage(CREATEPackageGame const &) = 0;
    virtual void onGetBEAMPackage(BEAMPackageGame const &) = 0;
    virtual void onGetSHOTPackage(SHOTPackageGame const &) = 0;
    virtual void onGetDIEPackage(DIEPackageGame const &) = 0;
    virtual void onGetTAKEPackage(TAKEPackageGame const &) = 0;
    virtual void onGetDROPPackage(DROPPackageGame const &) = 0;
    virtual void onGetMOVEPackage(MOVEPackageGame const &) = 0;
    virtual void onGetLAUNCHPackage(LAUNCHPackageGame const &) = 0;
};

#endif //RTYPE_IPROTOCOLGAMEHANDLER_HPP
