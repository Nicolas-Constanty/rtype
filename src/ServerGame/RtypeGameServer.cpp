//
// Created by gaspar_q on 11/28/16.
//

#include <ServerGame/RtypeGameServer.hpp>

RtypeGameServer::RtypeGameServer(SaltyEngine::GameObject *obj) :
        AUDPServer(dispatcher),
        SaltyBehaviour(obj),
        dispatcher()
{

}

RtypeGameServer::~RtypeGameServer()
{

}

void RtypeGameServer::OnDataReceived(unsigned int )
{
    std::cout << "Hey j'ai reçu " << buff << std::endl;
}

void RtypeGameServer::OnDataSent(unsigned int len)
{
    std::cout << "On send des choses: " << len << std::endl;
}

void RtypeGameServer::Start()
{
    sock.Open();
    sock.Listen(4242);
    dispatcher.Watch(this, Network::Core::NativeSocketIOOperationDispatcher::READ);
    dispatcher.setTimeout({0, 0});
}

void RtypeGameServer::Update()
{
    dispatcher.Poll();
}
