//
// Created by victor on 21/11/16.
//

#ifndef RTYPE_IRTYPEPROTOCOLMANAGER_HPP
#define RTYPE_IRTYPEPROTOCOLMANAGER_HPP

#include <cstring>

class IRTypeProtocolManager {
public:
    virtual ~IRTypeProtocolManager() {}

public:
    virtual bool handleProtocol(unsigned char *byte, size_t) = 0;
};

#endif //RTYPE_IRTYPEPROTOCOLMANAGER_HPP
