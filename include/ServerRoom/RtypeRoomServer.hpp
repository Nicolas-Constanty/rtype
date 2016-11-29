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
    RtypeRoomServer(Network::Core::NativeSocketIOOperationDispatcher &dispatcher) :
            Network::TCP::ATCPServer<DefaultTCPConnection>(dispatcher)
    {
        Start(4242);
    }

    virtual ~RtypeRoomServer()
    {
        Stop();
    }

public:
    virtual void OnDataReceived(unsigned int)
    {
        std::cout << "New client accepted" << std::endl;
    }

    virtual void OnDataSent(unsigned int len)
    {
        std::cout << "Number of bytes sent: " << len << std::endl;
    }
};


#endif //RTYPE_RTYPEROOMSERVER_HPP
