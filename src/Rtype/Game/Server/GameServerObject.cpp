//
// Created by gaspar_q on 12/6/16.
//

#include <Common/Singleton.hpp>
#include <SaltyEngine/SaltyEngine.hpp>
#include <Rtype/Game/Server/GameServerObject.hpp>
#include <Rtype/Game/Client/GameManager.hpp>

Rtype::Game::Server::GameServerObject::GameServerObject(SaltyEngine::GameObject *obj, const uint16_t port, const size_t maxClient, const uint32_t secret, const std::string &map) :
    SaltyEngine::SaltyBehaviour(obj),
    secret(secret),
    m_maxClient(maxClient),
    port(port),
    map(map),
    server(nullptr),
    dispatcher(),
    manager(NULL),
    running(false)
{

}

Rtype::Game::Server::GameServerObject::~GameServerObject()
{
    delete(server);
}

void Rtype::Game::Server::GameServerObject::Start()
{
    server = new RtypeGameServer(dispatcher, m_maxClient, map);
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
        Singleton<SaltyEngine::Engine>::Instance().Stop();
    }
    manager = gameObject->GetComponent<GameManager>();
    server->setManager(manager);
}

void Rtype::Game::Server::GameServerObject::Update()
{
    if (running)
       dispatcher.Poll();
}

SaltyEngine::Component *Rtype::Game::Server::GameServerObject::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new GameServerObject(obj, port, m_maxClient, secret, map);
}
