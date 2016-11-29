//
// Created by victor on 29/11/16.
//

#ifndef RTYPE_RTYPEROOMSERVER_HPP
#define RTYPE_RTYPEROOMSERVER_HPP

#include <iostream>
#include <Network/TCP/ATCPServer.hpp>
#include "ServerRoom/DefaultTCPConnection.hpp"

class RtypeRoomServer : public Network::TCP::ATCPServer<DefaultTCPConnection>
{
public:
    RtypeRoomServer(Network::Core::NativeSocketIOOperationDispatcher &dispatcher);
    virtual ~RtypeRoomServer();

public:
    virtual void OnDataReceived(unsigned int);
    virtual void OnDataSent(unsigned int len);
};


#endif //RTYPE_RTYPEROOMSERVER_HPP
