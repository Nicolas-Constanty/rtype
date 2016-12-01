//
// Created by victor on 21/11/16.
//

#include <iostream>
#include <Protocol/Room/RoomPackageFactory.hpp>
#include "Protocol/Room/RTypeProtocolRoomManager.hpp"

const RTypeProtocolRoomManager::RoomID RTypeProtocolRoomManager::AUTHENTICATEID = RTypeProtocolRoomManager::RoomID(ROOMAUTHENTICATE, sizeof(AUTHENTICATEPackageRoom));
const RTypeProtocolRoomManager::RoomID RTypeProtocolRoomManager::CREATEID = RTypeProtocolRoomManager::RoomID(ROOMCREATE, sizeof(CREATEPackageRoom));
const RTypeProtocolRoomManager::RoomID RTypeProtocolRoomManager::FAILUREID = RTypeProtocolRoomManager::RoomID(ROOMFAILURE, sizeof(FAILUREPackageRoom));
const RTypeProtocolRoomManager::RoomID RTypeProtocolRoomManager::GETID = RTypeProtocolRoomManager::RoomID(ROOMGET, sizeof(GETPackageRoom));
const RTypeProtocolRoomManager::RoomID RTypeProtocolRoomManager::JOINID = RTypeProtocolRoomManager::RoomID(ROOMJOIN, sizeof(JOINPackageRoom));
const RTypeProtocolRoomManager::RoomID RTypeProtocolRoomManager::PLUGGEDID = RTypeProtocolRoomManager::RoomID(ROOMPLUGGED, sizeof(PLUGGEDPackageRoom));
const RTypeProtocolRoomManager::RoomID RTypeProtocolRoomManager::SWAPID = RTypeProtocolRoomManager::RoomID(ROOMSWAP, sizeof(SWAPPackageRoom));
const RTypeProtocolRoomManager::RoomID RTypeProtocolRoomManager::QUITID = RTypeProtocolRoomManager::RoomID(ROOMQUIT, sizeof(QUITPackageRoom));
const RTypeProtocolRoomManager::RoomID RTypeProtocolRoomManager::LAUNCHID = RTypeProtocolRoomManager::RoomID(ROOMLAUNCH, sizeof(LAUNCHPackageRoom));
const RTypeProtocolRoomManager::RoomID RTypeProtocolRoomManager::DELETEID = RTypeProtocolRoomManager::RoomID(ROOMDELETE, sizeof(DELETEPackageRoom));

RTypeProtocolRoomManager::RTypeProtocolRoomManager(IProtocolRoomHandler &protocolRoomHandler)
        : protocolRoomHandler(protocolRoomHandler) {
    fptr[AUTHENTICATEID] = (MFP)&IProtocolRoomHandler::onGetAUTHENTICATEPackage;
    fptr[CREATEID] = (MFP)&IProtocolRoomHandler::onGetCREATEPackage;
    fptr[FAILUREID] = (MFP)&IProtocolRoomHandler::onGetFAILUREPackage;
    fptr[GETID] = (MFP)&IProtocolRoomHandler::onGetGETPackage;
    fptr[JOINID] = (MFP)&IProtocolRoomHandler::onGetJOINPackage;
    fptr[PLUGGEDID] = (MFP)&IProtocolRoomHandler::onGetPLUGGEDPackage;
    fptr[SWAPID] = (MFP)&IProtocolRoomHandler::onGetSWAPPackage;
    fptr[QUITID] = (MFP)&IProtocolRoomHandler::onGetQUITPackage;
    fptr[LAUNCHID] = (MFP)&IProtocolRoomHandler::onGetLAUNCHPackage;
    fptr[DELETEID] = (MFP)&IProtocolRoomHandler::onGetDELETEPackage;
}

RTypeProtocolRoomManager::~RTypeProtocolRoomManager() {

}

bool RTypeProtocolRoomManager::handleProtocol(unsigned char *byte, size_t size) {
    PackageRoomHeader *packageRoomHeader;

    if ((packageRoomHeader = getHeaderFrom(byte, size))) {
        if (isPackageHeaderValid(packageRoomHeader)) {
            std::map<RoomID, MFP>::iterator it = fptr.find(RTypeProtocolRoomManager::RoomID(static_cast<RoomPurpose>(packageRoomHeader->purpose),
                                                                                                 packageRoomHeader->length));
            if (it != fptr.end() && packageRoomHeader->length <= size) {
                (protocolRoomHandler.*(it->second))(*packageRoomHeader);
                return true;
            }
        }
    }
    return false;
}

PackageRoomHeader *RTypeProtocolRoomManager::getHeaderFrom(unsigned char *byte, size_t len) {
    PackageRoomHeader *packageRoomHeader;

    if (len < sizeof(PackageRoomHeader)) {
        return (NULL);
    }
    packageRoomHeader = (PackageRoomHeader *)byte;
    return (packageRoomHeader);
}

bool RTypeProtocolRoomManager::isPackageHeaderValid(PackageRoomHeader *packageRoomHeader) {
    return packageRoomHeader->headerRoomInfo.verLeft == 0
           && packageRoomHeader->headerRoomInfo.verMiddle == 0
           && packageRoomHeader->headerRoomInfo.verRight == 1
           && packageRoomHeader->headerRoomInfo.reservedLeftOne == 1
           && packageRoomHeader->headerRoomInfo.reservedLeftZero == 0
           && packageRoomHeader->headerRoomInfo.reservedMiddleOne == 1
           && packageRoomHeader->headerRoomInfo.reservedRightZero == 0
           && packageRoomHeader->headerRoomInfo.reservedRightOne == 1;
}
