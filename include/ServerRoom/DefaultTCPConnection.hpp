//
// Created by victor on 29/11/16.
//

#ifndef RTYPE_DEFAULTTCPCONNECTION_HPP
#define RTYPE_DEFAULTTCPCONNECTION_HPP

#include <Network/TCP/ATCPClient.hpp>

class DefaultTCPConnection : public Network::TCP::ATCPClient
{
public:
    DefaultTCPConnection(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
    DefaultTCPConnection(Network::Core::BasicConnection &ref);
    virtual ~DefaultTCPConnection();

public:
    virtual void OnDataReceived(unsigned int len);
    virtual void OnDataSent(unsigned int len);
};

#endif //RTYPE_DEFAULTTCPCONNECTION_HPP
