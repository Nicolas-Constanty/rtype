//
// Created by victor on 21/11/16.
//

#include <iostream>
#include <Protocol/Game/GamePackageFactory.hpp>
#include "Protocol/Game/RTypeProtocolGameManager.hpp"

const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::MOVEID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEMOVE, sizeof(MOVEPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::TAKEID = RTypeProtocolGameManager::GameID(GamePurpose::GAMETAKE, sizeof(TAKEPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::BEAMID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEBEAM, sizeof(BEAMPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::CALLID = RTypeProtocolGameManager::GameID(GamePurpose::GAMECALL, sizeof(CALLPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::DIEID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEDIE, sizeof(DIEPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::CREATEID = RTypeProtocolGameManager::GameID(GamePurpose::GAMECREATE, sizeof(CREATEPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::LAUNCHID = RTypeProtocolGameManager::GameID(GamePurpose::GAMELAUNCH, sizeof(LAUNCHPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::STATUSID = RTypeProtocolGameManager::GameID(GamePurpose::GAMESTATUS, sizeof(STATUSPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::AUTHENTICATEID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEAUTHENTICATE, sizeof(AUTHENTICATEPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::PINGID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEPING, sizeof(PINGPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::SHOTID = RTypeProtocolGameManager::GameID(GamePurpose::GAMESHOT, sizeof(SHOTPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::REBORNID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEREBORN, sizeof(PINGPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::FAILUREID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEFAILURE, sizeof(SHOTPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::DISCONNECTID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEDISCONNECT, sizeof(DISCONNECTPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::ENEMYSHOTID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEENEMYSHOT, sizeof(ENEMYSHOTPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::UPGRADEID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEUPGRADE, sizeof(UPGRADEPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::MATEID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEMATE, sizeof(MATEPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::GAMEOVERID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEGAMEOVER, sizeof(GAMEOVERPackageGame));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::DEATHID = RTypeProtocolGameManager::GameID(GamePurpose::GAMEDEATH, sizeof(DEATHPackage));
const RTypeProtocolGameManager::GameID RTypeProtocolGameManager::RECONNECTID = RTypeProtocolGameManager::GameID(GamePurpose::GAMERECONNECT, sizeof(RECONNECTPackageGame));

RTypeProtocolGameManager::RTypeProtocolGameManager(IProtocolGameHandler &protocolGameHandler)
        : protocolGameHandler(protocolGameHandler) {
    fptr[MOVEID] = (MFP)&IProtocolGameHandler::onGetMOVEPackage;
    fptr[SHOTID] = (MFP)&IProtocolGameHandler::onGetSHOTPackage;
    fptr[TAKEID] = (MFP)&IProtocolGameHandler::onGetTAKEPackage;
    fptr[BEAMID] = (MFP)&IProtocolGameHandler::onGetBEAMPackage;
    fptr[CALLID] = (MFP)&IProtocolGameHandler::onGetCALLPackage;
    fptr[DIEID] = (MFP)&IProtocolGameHandler::onGetDIEPackage;
    fptr[CREATEID] = (MFP)&IProtocolGameHandler::onGetCREATEPackage;
    fptr[LAUNCHID] = (MFP)&IProtocolGameHandler::onGetLAUNCHPackage;
    fptr[STATUSID] = (MFP)&IProtocolGameHandler::onGetSTATUSPackage;
    fptr[AUTHENTICATEID] = (MFP)&IProtocolGameHandler::onGetAUTHENTICATEPackage;
    fptr[PINGID] = (MFP)&IProtocolGameHandler::onGetPINGPackage;
    fptr[REBORNID] = (MFP)&IProtocolGameHandler::onGetREBORNPackage;
    fptr[FAILUREID] = (MFP)&IProtocolGameHandler::onGetFAILUREPackage;
    fptr[DISCONNECTID] = (MFP)&IProtocolGameHandler::onGetDISCONNECTPackage;
    fptr[ENEMYSHOTID] = (MFP)&IProtocolGameHandler::onGetENEMYSHOTPackage;
    fptr[UPGRADEID] = (MFP)&IProtocolGameHandler::onGetUPGRADEPackage;
    fptr[MATEID] = (MFP)&IProtocolGameHandler::onGetMATEPackage;
    fptr[GAMEOVERID] = (MFP)&IProtocolGameHandler::onGetGAMEOVERPackage;
    fptr[DEATHID] = (MFP)&IProtocolGameHandler::onGetDEATHPackage;
    fptr[RECONNECTID] = (MFP)&IProtocolGameHandler::onGetRECONNECTPackage;
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
