//
// Created by gaspar_q on 11/30/16.
//

#include <Rtype/Game/Server/Room.hpp>
#include <SaltyEngine/SaltyEngine.hpp>
#include <SaltyEngine/SFML/Scene.hpp>
#include <Rtype/Game/Server/GameServerObject.hpp>

Rtype::Game::Server::Room::Room()
{

}

Rtype::Game::Server::Room::~Room()
{

}

void Rtype::Game::Server::Room::Start(const uint16_t port, const size_t max, const uint32_t secret, uint16_t map)
{
    // Create Scene
    SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

    // Create player
    SaltyEngine::GameObject *serverGame = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());

    if (serverGame == NULL)
        throw std::runtime_error("Fatal error: Cannot Instantiate a gameobject");

    //Adding GameServerObject as component for network gestion
    serverGame->AddComponent<Rtype::Game::Server::GameServerObject>(port, max > 4 ? 4 : max, secret, map);

    //Adding object to scene
    *scene << serverGame;

    // Push scene int SaltyEngine
    Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;
}

void Rtype::Game::Server::Room::Run()
{
    // Run the SaltyEngine with default Scene 0
    Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
}