//
// Created by gaspar_q on 12/6/16.
//

#include <Common/Singleton.hpp>
#include <SaltyEngine/SaltyEngine.hpp>
#include <Rtype/Game/Server/GameServerObject.hpp>

Rtype::Game::Server::GameServerObject::GameServerObject(SaltyEngine::GameObject *obj, const uint16_t port, const size_t maxClient, const uint32_t secret, uint16_t map) :
    SaltyEngine::SaltyBehaviour(obj),
    secret(secret),
    port(port),
    map(map),
    server(new RtypeGameServer(dispatcher, maxClient)),
    dispatcher(),
    running(false)
{

}

Rtype::Game::Server::GameServerObject::~GameServerObject()
{
    delete(server);
}

void Rtype::Game::Server::GameServerObject::Start()
{
    if (secret != 0)
    {
        server->setSecret(secret);
        server->setSecure(true);
    }
    try
    {
        server->Start(port);
        running = true;
        dispatcher.Watch(server, Network::Core::NativeSocketIOOperationDispatcher::READ);
        dispatcher.setTimeout({0, 0});
    }
    catch (Network::Socket::SocketException const &err)
    {
        std::cout << "[\x1b[31mERROR\x1b[0m]: Cannot start server: " << err.what() << std::endl;
        Singleton<SaltyEngine::SaltyEngine>::Instance().Stop();
    }
}

void Rtype::Game::Server::GameServerObject::Update()
{
    if (running)
       dispatcher.Poll();
}
