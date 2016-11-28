//
// Created by victor on 21/11/16.
//

#include <iostream>
#include <Protocol/Server/ServerPackageFactory.hpp>
#include "Protocol/Server/RTypeProtocolServerManager.hpp"

const RTypeProtocolServerManager::ServerID RTypeProtocolServerManager::AUTHENTICATEID = RTypeProtocolServerManager::ServerID(SERVERAUTHENTICATE, sizeof(AUTHENTICATEPackageServer));
const RTypeProtocolServerManager::ServerID RTypeProtocolServerManager::LAUNCHID = RTypeProtocolServerManager::ServerID(SERVERLAUNCH, sizeof(LAUNCHPackageServer));
const RTypeProtocolServerManager::ServerID RTypeProtocolServerManager::STATUSID = RTypeProtocolServerManager::ServerID(SERVERSTATUS, sizeof(STATUSPackageServer));

RTypeProtocolServerManager::RTypeProtocolServerManager(IProtocolServerHandler &protocolServerHandler)
        : protocolServerHandler(protocolServerHandler) {
    fptr[AUTHENTICATEID] = (MFP)&IProtocolServerHandler::onGetAUTHENTICATEPackage;
    fptr[LAUNCHID] = (MFP)&IProtocolServerHandler::onGetLAUNCHPackage;
    fptr[STATUSID] = (MFP)&IProtocolServerHandler::onGetSTATUSPackage;
}

RTypeProtocolServerManager::~RTypeProtocolServerManager() {

}

bool RTypeProtocolServerManager::handleProtocol(unsigned char *byte, size_t size) {
    PackageServerHeader *packageServerHeader;

    if ((packageServerHeader = getHeaderFrom(byte, size))) {
        if (isPackageHeaderValid(packageServerHeader)) {
            std::map<ServerID, MFP>::iterator it = fptr.find(RTypeProtocolServerManager::ServerID(static_cast<ServerPurpose>(packageServerHeader->purpose),
                                                                                                 packageServerHeader->length));
            if (it != fptr.end() && packageServerHeader->length <= size) {
                (protocolServerHandler.*(it->second))(*packageServerHeader);
                return true;
            }
        }
    }
    return false;
}

PackageServerHeader *RTypeProtocolServerManager::getHeaderFrom(unsigned char *byte, size_t len) {
    PackageServerHeader *packageServerHeader;

    if (len < sizeof(PackageServerHeader)) {
        return (NULL);
    }
    packageServerHeader = (PackageServerHeader *)byte;
    return (packageServerHeader);
}

bool RTypeProtocolServerManager::isPackageHeaderValid(PackageServerHeader *packageServerHeader) {
    return packageServerHeader->headerServerInfo.verLeft == 0
           && packageServerHeader->headerServerInfo.verMiddle == 1
           && packageServerHeader->headerServerInfo.verRight == 0
           && packageServerHeader->headerServerInfo.reservedLeftOne == 1
           && packageServerHeader->headerServerInfo.reservedLeftZero == 0
           && packageServerHeader->headerServerInfo.reservedMiddleOne == 1
           && packageServerHeader->headerServerInfo.reservedRightZero == 0
           && packageServerHeader->headerServerInfo.reservedRightOne == 1;
}
