//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_IRTYPEPROTOCOLMANAGER_HPP
#define RTYPE_IRTYPEPROTOCOLMANAGER_HPP

class IRTypeProtocolManager {
public:
    virtual ~IRTypeProtocolManager() {}

public:
    virtual bool handleProtocol(char *byte) = 0;
};

#endif //RTYPE_IRTYPEPROTOCOLMANAGER_HPP
