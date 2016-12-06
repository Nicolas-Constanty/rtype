//
// Created by gaspar_q on 11/28/16.
//

#include <ServerGame/RtypeGameServer.hpp>
#include <SaltyEngine/SFML/Scene.hpp>
#include <ServerGame/RtypeServerGameClient.hpp>

Rtype::RtypeGameServer::RtypeGameServer(SaltyEngine::GameObject *obj, const uint16_t port, const int maxSize) :
        AUDPServer(dispatcher),
        SaltyBehaviour(obj),
        dispatcher(),
        port(port),
        maxSize(maxSize),
        secure(false)
{

}

Rtype::RtypeGameServer::~RtypeGameServer()
{

}

bool Rtype::RtypeGameServer::OnDataReceived(unsigned int)
{
    if (clients->Streams().size() > maxSize)
    {
        std::cout << "Room full" << std::endl;
        newclient->Disconnect();
        return false;
    }

//    SaltyEngine::GameObject *ship = new SaltyEngine::GameObject("Player " + std::to_string(newclient->getId()));
    //todo add script component to <ship> and set it to <newclient> in order to call script functions in each network callback

    //    Singleton<SaltyEngine::SaltyEngine>::Instance()-> todo add gameobject to scene
//    SendData(*factory.create<CREATEPackageGame>(ship->transform.localPosition.x, ship->transform.localPosition.y, TODEFINE, ship->GetInstanceID())); todo define correspondance id for gameobjects type
    std::cout << "Hey j'ai reçu " << buff << std::endl;
    return true;
}

bool Rtype::RtypeGameServer::OnDataSent(unsigned int len)
{
    std::cout << "On send des choses: " << len << std::endl;
    return true;
}

void Rtype::RtypeGameServer::Start()
{
    Network::UDP::AUDPServer<RtypeServerGameClient>::Start(port);
    dispatcher.Watch(this, Network::Core::NativeSocketIOOperationDispatcher::READ);
    dispatcher.setTimeout({0, 0});
}

void Rtype::RtypeGameServer::Update()
{
    dispatcher.Poll();
}

void Rtype::RtypeGameServer::OnReadCheck()
{
    Network::UDP::AUDPServer<Rtype::RtypeServerGameClient>::OnReadCheck();
    for (std::list<std::unique_ptr<Network::Socket::ISockStreamHandler>>::iterator it = clients->Streams().begin(); it != clients->Streams().end();)
    {
        Rtype::RtypeServerGameClient *client = dynamic_cast<Rtype::RtypeServerGameClient *>(it->get());

        if (client && client->timedout())
        {
            client->Disconnect();
            it = clients->Streams().begin();
        }
        else
        {
//            std::cout << "Checking ping: " << client << std::endl;
            if (client && client->pong())
            {
//                std::cout << "===\e[32mPING\e[0m===" << std::endl;
                client->ping();
            }
            ++it;
        }
    }
}

void Rtype::RtypeGameServer::setSecret(uint32_t secret)
{
    this->secret = secret;
}

bool Rtype::RtypeGameServer::Authenticate(uint32_t secret)
{
    if (!secure)
        return true;
    return this->secret == secret;
}

void Rtype::RtypeGameServer::setSecure(bool security)
{
    secure = security;
}
