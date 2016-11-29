//
// Created by victor on 29/11/16.
//

#include "ServerRoom/RtypeRoomServer.hpp"

RtypeRoomServer::RtypeRoomServer(Network::Core::NativeSocketIOOperationDispatcher &dispatcher)
        : Network::TCP::ATCPServer<DefaultTCPConnection>(dispatcher)
{
    Start(4242);
}

RtypeRoomServer::~RtypeRoomServer()
{
    Stop();
}

void RtypeRoomServer::OnDataReceived(unsigned int)
{
    std::cout << "New client accepted" << std::endl;
}

void RtypeRoomServer::OnDataSent(unsigned int len)
{
    std::cout << "Number of bytes sent: " << len << std::endl;
}
