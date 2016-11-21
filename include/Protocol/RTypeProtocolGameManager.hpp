//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_RTYPEPROTOCOLGAMEMANAGER_HPP
#define RTYPE_RTYPEPROTOCOLGAMEMANAGER_HPP

#include "IRTypeProtocolManager.hpp"
#include "IProtocolGameHandler.hpp"

class RTypeProtocolGameManager : public IRTypeProtocolManager {
public:
    virtual ~RTypeProtocolGameManager();
    RTypeProtocolGameManager(IProtocolGameHandler &protocolGameHandler);

public:
    virtual bool handleProtocol(char *byte);

private:
    IProtocolGameHandler    &protocolGameHandler;
};

#endif //RTYPE_RTYPEPROTOCOLGAMEMANAGER_HPP
