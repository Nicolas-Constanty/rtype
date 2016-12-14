//
// Created by gaspar_q on 11/30/16.
//

#include <Rtype/Game/Server/Room.hpp>
#include <SaltyEngine/SaltyEngine.hpp>
#include <SaltyEngine/SFML/Scene.hpp>
#include <Rtype/Game/Server/GameServerObject.hpp>
#include <Rtype/Game/Client/GameManager.hpp>

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

    // Push scene int SaltyEngine
    Singleton<SaltyEngine::Engine>::Instance() << scene;

    // Create player
    SaltyEngine::GameObject *serverGame = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());

    serverGame->SetName("GameServer");

    if (serverGame == NULL)
        throw std::runtime_error("Fatal error: Cannot Instantiate a gameobject");

    //Adding GameServerObject as component for network gestion
    serverGame->AddComponent<Rtype::Game::Server::GameServerObject>(port, max > 4 ? 4 : max, secret, map);

    //Adding object to scene
    //*scene << serverGame;

}

void Rtype::Game::Server::Room::Run()
{
    // Run the SaltyEngine with default Scene 0
    Singleton<SaltyEngine::Engine>::Instance().Run();
}