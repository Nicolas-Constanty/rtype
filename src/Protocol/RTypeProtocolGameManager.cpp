//
// Created by victor on 21/11/16.
//

#include "Protocol/RTypeProtocolGameManager.hpp"

RTypeProtocolGameManager::RTypeProtocolGameManager(IProtocolGameHandler &protocolGameHandler)
        : protocolGameHandler(protocolGameHandler) {

}

RTypeProtocolGameManager::~RTypeProtocolGameManager() {

}

bool RTypeProtocolGameManager::handleProtocol(char *byte) {
    BEAMPackageGame beam(0, 1);

    this->protocolGameHandler.onGetBEAMPackage(beam);
    return false;
}