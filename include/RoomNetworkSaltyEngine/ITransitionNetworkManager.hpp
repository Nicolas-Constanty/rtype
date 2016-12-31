//
// Created by gouet_v on 12/31/16.
//

#ifndef RTYPE_ITRANSITIONNETWORKMANAGER_HPP
#define RTYPE_ITRANSITIONNETWORKMANAGER_HPP

#include "Protocol/Room/ProtocolRoomPackage.hpp"

class ITransitionNetworkManager {
public:
    virtual ~ITransitionNetworkManager() {}

public:
    virtual void onGetAUTHENTICATE(AUTHENTICATEPackageRoom const &) = 0;
    virtual void onGetCREATE(CREATEPackageRoom const &) = 0;
    virtual void onGetJOIN(JOINPackageRoom const &) = 0;
    virtual void onGetQUIT(QUITPackageRoom const &) = 0;
    virtual void onGetPLUGGED(PLUGGEDPackageRoom const &) = 0;
    virtual void onGetSWAP(SWAPPackageRoom const &) = 0;
    virtual void onGetGET(GETPackageRoom const &) = 0;
    virtual void onGetFAILURE(FAILUREPackageRoom const &) = 0;
    virtual void onGetLAUNCH(LAUNCHPackageRoom const &) = 0;
    virtual void onGetDELETE(DELETEPackageRoom const &) = 0;
    virtual void onGetCHAT(CHATPackageRoom const &) = 0;
};

#endif //RTYPE_ITRANSITIONNETWORKMANAGER_HPP
