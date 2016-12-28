//
// Created by gaspar_q on 11/30/16.
//

#include <Rtype/Game/Server/Room.hpp>
#include <Rtype/Game/Client/GameManager.hpp>
#include "SaltyEngine/SFML.hpp"

Rtype::Game::Server::Room::Room()
{

}

Rtype::Game::Server::Room::~Room()
{

}

void Rtype::Game::Server::Room::Start(const uint16_t port, const size_t max, const uint32_t secret, uint16_t map)
{
    // Create Scene
    //SaltyEngine::SFML::Renderer *renderer = new SaltyEngine::SFML::Renderer(sf::VideoMode(1280, 720), "R-Type Launcher");
    //Singleton<SaltyEngine::Engine>::Instance().SetRenderer(renderer);
    unsigned int x = 960;
    unsigned int y = 540;
    SaltyEngine::SFML::PhysicsHandler *ph = new SaltyEngine::SFML::PhysicsHandler(x, y, true);
    SaltyEngine::Engine::Instance().SetPhysicsHandler(ph);

//    SaltyEngine::Engine::Instance().SetFrameRate(30);

    SaltyEngine::SFML::Scene *scene = new SaltyEngine::SFML::Scene();

    // Push scene int SaltyEngine
    SaltyEngine::Engine::Instance() << scene;

	std::cout << &SaltyEngine::Engine::Instance() << std::endl;

    // Create player
    SaltyEngine::GameObject *serverGame = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());


    if (serverGame == NULL)
    {
        throw std::runtime_error("Fatal error: Cannot Instantiate a gameobject");
    }

    serverGame->SetName("Rtype");
    //Adding GameServerObject as component for network gestion
    serverGame->AddComponent<Rtype::Game::Server::GameServerObject>(port, max > 4 ? 4 : max, secret, map);
    serverGame->AddComponent<GameManager>();

    //Adding object to scene
    //*scene << serverGame;
    serverGame->AddComponent<SaltyEngine::SFML::BoxCollider2D>(
            sf::Vector2u(40, 40)
    );
//    serverGame->transform.position = SaltyEngine::Vector2(20, 20);
    serverGame->transform.SetPosition(SaltyEngine::Vector2(20, 20));
}

void Rtype::Game::Server::Room::Run()
{
    // Run the SaltyEngine with default Scene 0
    SaltyEngine::Engine::Instance().Run();
}