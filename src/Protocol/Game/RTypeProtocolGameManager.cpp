//
// Created by victor on 21/11/16.
//

#include <iostream>
#include <Protocol/Game/GamePackageFactory.hpp>
#include "Protocol/Game/RTypeProtocolGameManager.hpp"

const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::MOVEID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEMOVE, sizeof(MOVEPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::TAKEID = RTypeProtocolGameManager::GameID(GamePurpose::GAMETAKE, sizeof(TAKEPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::BEAMID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEBEAM, sizeof(BEAMPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::DROPID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEDROP, sizeof(DROPPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::DIEID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEDIE, sizeof(DIEPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::CREATEID = RTypeProtocolGameManager::GameID(GamePurpose::GAMECREATE, sizeof(CREATEPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::LAUNCHID = RTypeProtocolGameManager::GameID(GamePurpose::GAMELAUNCH, sizeof(LAUNCHPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::STATUSID = RTypeProtocolGameManager::GameID(GamePurpose::GAMESTATUS, sizeof(STATUSPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::AUTHENTICATEID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEAUTHENTICATE, sizeof(AUTHENTICATEPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::PINGID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEPING, sizeof(PINGPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::SHOTID = RTypeProtocolGameManager::GameID(GamePurpose::GAMESHOT, sizeof(SHOTPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::REBORNID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEREBORN, sizeof(PINGPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::FAILUREID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEFAILURE, sizeof(SHOTPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::INPUTID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEINPUT, sizeof(INPUTPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::DISCONNECTID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEDISCONNECT, sizeof(DISCONNECTPackageGame));

RTypeProtocolGameManager::RTypeProtocolGameManager(IProtocolGameHandler &protocolGameHandler)
        : protocolGameHandler(protocolGameHandler) {
    fptr[MOVEID] = (MFP)&IProtocolGameHandler::onGetMOVEPackage;
    fptr[SHOTID] = (MFP)&IProtocolGameHandler::onGetSHOTPackage;
    fptr[TAKEID] = (MFP)&IProtocolGameHandler::onGetTAKEPackage;
    fptr[BEAMID] = (MFP)&IProtocolGameHandler::onGetBEAMPackage;
    fptr[DROPID] = (MFP)&IProtocolGameHandler::onGetDROPPackage;
    fptr[DIEID] = (MFP)&IProtocolGameHandler::onGetDIEPackage;
    fptr[CREATEID] = (MFP)&IProtocolGameHandler::onGetCREATEPackage;
    fptr[LAUNCHID] = (MFP)&IProtocolGameHandler::onGetLAUNCHPackage;
    fptr[STATUSID] = (MFP)&IProtocolGameHandler::onGetSTATUSPackage;
    fptr[AUTHENTICATEID] = (MFP)&IProtocolGameHandler::onGetAUTHENTICATEPackage;
    fptr[PINGID] = (MFP)&IProtocolGameHandler::onGetPINGPackage;
    fptr[REBORNID] = (MFP)&IProtocolGameHandler::onGetREBORNPackage;
    fptr[FAILUREID] = (MFP)&IProtocolGameHandler::onGetFAILUREPackage;
    fptr[INPUTID] = (MFP)&IProtocolGameHandler::onGetINPUTPackage;
    fptr[DISCONNECTID] = (MFP)&IProtocolGameHandler::onGetDISCONNECTPackage;
}

RTypeProtocolGameManager::~RTypeProtocolGameManager() {

}

bool RTypeProtocolGameManager::handleProtocol(unsigned char *byte, size_t size) {
    PackageGameHeader *packageGameHeader;

    if ((packageGameHeader = getHeaderFrom(byte, size))) {
        if (isPackageHeaderValid(packageGameHeader)) {
            std::map<GameID, MFP>::iterator it = fptr.find(RTypeProtocolGameManager::GameID(static_cast<GamePurpose>(packageGameHeader->purpose),
                                                                                                 packageGameHeader->length));
            if (it != fptr.end() && packageGameHeader->length <= size) {
                (protocolGameHandler.*(it->second))(*packageGameHeader);
                return true;
            }
        }
    }
    return false;
}

PackageGameHeader *RTypeProtocolGameManager::getHeaderFrom(unsigned char *byte, size_t len) {
    PackageGameHeader *packageGameHeader;

    if (len < sizeof(PackageGameHeader)) {
        return (NULL);
    }
    packageGameHeader = (PackageGameHeader *)byte;
    return (packageGameHeader);
}

bool RTypeProtocolGameManager::isPackageHeaderValid(PackageGameHeader *packageGameHeader) {
    return packageGameHeader->headerGameInfo.verLeft == 0
           && packageGameHeader->headerGameInfo.verRight == 1
           && packageGameHeader->headerGameInfo.reservedLeftOne == 1
           && packageGameHeader->headerGameInfo.reservedLeftZero == 0
           && packageGameHeader->headerGameInfo.reservedMiddleOne == 1
           && packageGameHeader->headerGameInfo.reservedRightZero == 0
           && packageGameHeader->headerGameInfo.reservedRightOne == 1;
}
