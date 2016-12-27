//
// Created by gaspar_q on 11/11/16.
//

#ifndef SPIDER_SERVER_ICONNECTABLE_HPP
#define SPIDER_SERVER_ICONNECTABLE_HPP

#include <string>
#include "Common/DLLexport.hpp"

class LIB_EXPORT IConnectable
{
public:
    virtual ~IConnectable(){}

public:
    virtual void Connect(std::string const &ip, int port) = 0;
    virtual void Disconnect() = 0;
    virtual void Accept() = 0;
};

#endif //SPIDER_SERVER_ICONNECTABLE_HPP
