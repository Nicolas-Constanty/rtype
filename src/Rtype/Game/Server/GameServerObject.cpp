//
// Created by gaspar_q on 12/6/16.
//

#include <Rtype/Game/Server/GameServerObject.hpp>

Rtype::Game::Server::GameServerObject::GameServerObject(SaltyEngine::GameObject *obj, const uint16_t port, const int maxClient, const uint32_t secret) :
    SaltyEngine::SaltyBehaviour(obj),
    secret(secret),
    port(port),
    server(new RtypeGameServer(dispatcher, maxClient)),
    dispatcher()
{

}

Rtype::Game::Server::GameServerObject::~GameServerObject()
{
    delete(server);
}

void Rtype::Game::Server::GameServerObject::Start()
{
    server->Start(port);
    dispatcher.Watch(server, Network::Core::NativeSocketIOOperationDispatcher::READ);
    dispatcher.setTimeout({0, 0});
    if (secret != 0)
    {
        server->setSecret(secret);
        server->setSecure(true);
    }
}

void Rtype::Game::Server::GameServerObject::Update()
{
    dispatcher.Poll();
}
