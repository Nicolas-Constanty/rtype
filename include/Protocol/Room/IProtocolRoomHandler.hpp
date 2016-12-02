//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_IPROTOCOLROOMHANDLER_HPP
#define RTYPE_IPROTOCOLROOMHANDLER_HPP

#include "ProtocolRoomPackage.hpp"

class IProtocolRoomHandler {
public:
    virtual ~IProtocolRoomHandler() {}

public:
    virtual void onGetAUTHENTICATEPackage(AUTHENTICATEPackageRoom const &) = 0;
    virtual void onGetCREATEPackage(CREATEPackageRoom const &) = 0;
    virtual void onGetJOINPackage(JOINPackageRoom const &) = 0;
    virtual void onGetQUITPackage(QUITPackageRoom const &) = 0;
    virtual void onGetPLUGGEDPackage(PLUGGEDPackageRoom const &) = 0;
    virtual void onGetSWAPPackage(SWAPPackageRoom const &) = 0;
    virtual void onGetGETPackage(GETPackageRoom const &) = 0;
    virtual void onGetFAILUREPackage(FAILUREPackageRoom const &) = 0;
    virtual void onGetLAUNCHPackage(LAUNCHPackageRoom const &) = 0;
    virtual void onGetDELETEPackage(DELETEPackageRoom const &) = 0;
    virtual void onGetCHATPackage(CHATPackageRoom const &) = 0;
};

#endif //RTYPE_IPROTOCOLROOMHANDLER_HPP
