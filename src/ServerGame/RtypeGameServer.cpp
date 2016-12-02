//
// Created by gaspar_q on 11/28/16.
//

#include <ServerGame/RtypeGameServer.hpp>
#include <SaltyEngine/Scene.hpp>

Rtype::RtypeGameServer::RtypeGameServer(SaltyEngine::GameObject *obj, const uint16_t port, const int maxSize) :
        AUDPServer(dispatcher),
        SaltyBehaviour(obj),
        dispatcher(),
        port(port),
        maxSize(maxSize)
{

}

Rtype::RtypeGameServer::~RtypeGameServer()
{

}

void Rtype::RtypeGameServer::OnDataReceived(unsigned int)
{
    if (clients->Streams().size() > maxSize)
    {
        newclient->Disconnect();
        return;
    }

    SaltyEngine::GameObject *ship = new SaltyEngine::GameObject("Player " + std::to_string(newclient->getId()));
    //todo add script component to <ship> and set it to <newclient> in order to call script functions in each network callback

    //    Singleton<SaltyEngine::SaltyEngine>::Instance()-> todo add gameobject to scene
//    SendData(*factory.create<CREATEPackageGame>(ship->transform.localPosition.x, ship->transform.localPosition.y, TODEFINE, ship->GetInstanceID())); todo define correspondance id for gameobjects type
    std::cout << "Hey j'ai reçu " << buff << std::endl;
}

void Rtype::RtypeGameServer::OnDataSent(unsigned int len)
{
    std::cout << "On send des choses: " << len << std::endl;
}

void Rtype::RtypeGameServer::Start()
{
    Network::UDP::AUDPServer<RtypeGameClient>::Start(port);
    dispatcher.Watch(this, Network::Core::NativeSocketIOOperationDispatcher::READ);
    dispatcher.setTimeout({0, 0});
}

void Rtype::RtypeGameServer::Update()
{
    dispatcher.Poll();
}
