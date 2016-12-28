//
// Created by gaspar_q on 11/11/16.
//

#ifndef SPIDER_SERVER_IACCEPTOR_HPP
#define SPIDER_SERVER_IACCEPTOR_HPP

#include "IConnectable.hpp"

class PREF_EXPORT IAcceptor
{
public:
    virtual ~IAcceptor(){}

public:
    virtual bool Accept() = 0;
    virtual bool Disconnect(ATCPConnection *connectable) = 0;
};

#endif //SPIDER_SERVER_IACCEPTOR_HPP
