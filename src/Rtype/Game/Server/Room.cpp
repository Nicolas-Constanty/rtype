//
// Created by gaspar_q on 11/30/16.
//

#include <Rtype/Game/Server/Room.hpp>
#include <SaltyEngine/SaltyEngine.hpp>
#include <SaltyEngine/SFML/Scene.hpp>

Rtype::Game::Server::Room::Room()
{

}

Rtype::Game::Server::Room::~Room()
{

}

void Rtype::Game::Server::Room::Start(const uint16_t port)
{
    // Create Scene
    SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

    // Create player
    SaltyEngine::GameObject *serverGame = new SaltyEngine::GameObject("Server");

    server = serverGame->AddComponent<Rtype::Game::Server::RtypeGameServer>(port);

    *scene << serverGame;

    // Push scene int SaltyEngine
    Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;
}

void Rtype::Game::Server::Room::Run()
{
    // Run the SaltyEngine with default Scene 0
    Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
}

void Rtype::Game::Server::Room::Stop()
{
    server->Disconnect();
}

void Rtype::Game::Server::Room::setSecure(bool security)
{
    server->setSecure(security);
}

void Rtype::Game::Server::Room::setSecret(uint32_t secret)
{
    server->setSecret(secret);
}