//
// Created by victor on 29/11/16.
//

#ifndef RTYPE_PROTOCOLROOMAUTHENTICATEHANDLER_HPP
#define RTYPE_PROTOCOLROOMAUTHENTICATEHANDLER_HPP

#include "Protocol/Room/IProtocolRoomHandler.hpp"

class ProtocolRoomAuthenticateHandler : public IProtocolRoomHandler {
public:
    virtual ~ProtocolRoomAuthenticateHandler() {}

    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &) = 0;
    virtual void onGetFAILUREPackage(FAILUREPackageRoom const &) = 0;
    virtual void onGetCREATEPackage(CREATEPackageRoom const &) {}
    virtual void onGetJOINPackage(JOINPackageRoom const &) {}
    virtual void onGetQUITPackage(QUITPackageRoom const &) {}
    virtual void onGetPLUGGEDPackage(PLUGGEDPackageRoom const &) {}
    virtual void onGetSWAPPackage(SWAPPackageRoom const &) {}
    virtual void onGetGETPackage(GETPackageRoom const &) {}
    virtual void onGetLAUNCHPackage(LAUNCHPackageRoom const &) {}
    virtual void onGetDELETEPackage(DELETEPackageRoom const &) {}
    virtual void onGetCHATPackage(CHATPackageRoom const &) {}
};

#endif //RTYPE_PROTOCOLROOMAUTHENTICATE_HPP
