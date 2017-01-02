//
// Created by gaspar_q on 11/30/16.
//

#include <Rtype/Game/Server/Room.hpp>
#include <Rtype/Game/Client/GameManager.hpp>
#include <SaltyEngine/SFML/SFMLSceneLoader.hpp>
#include "SaltyEngine/SFML.hpp"

Rtype::Game::Server::Room::Room()
{

}

Rtype::Game::Server::Room::~Room()
{

}

void Rtype::Game::Server::Room::Start(int ac, char **av, const uint16_t port, const size_t max, const uint32_t secret, const std::string &map)
{
//    SaltyEngine::GameObject *serverGame = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());

//    if (serverGame == NULL)
//    {
//        throw std::runtime_error("Fatal error: Cannot Instantiate a gameobject");
//    }

//    serverGame->SetName("GameManager");
    //Adding GameServerObject as component for network gestion
//    serverGame->AddComponent<Rtype::Game::Server::GameServerObject>(port, max > 4 ? 4 : max, secret, map);
//    serverGame->AddComponent<GameManager>();

    //Adding object to scene
    //*scene << serverGame;
//    serverGame->AddComponent<SaltyEngine::SFML::BoxCollider2D>(
//            sf::Vector2u(40, 40)
//    );
//    serverGame->transform.position = SaltyEngine::Vector2(20, 20);
//    serverGame->transform.SetPosition(SaltyEngine::Vector2(20, 20));

    // TODO : faire en sorte que le GameManager ait le Rtype::Game::Server::GameServerObject pour la connexion
    SaltyEngine::Engine::Instance().SetArguments(ac, (const char**)av);
    SaltyEngine::Engine::Instance().SetSceneLoader(new SaltyEngine::SFML::SFMLSceneLoader());
    SaltyEngine::Engine::Instance().LoadScene(map);
}

void Rtype::Game::Server::Room::Run()
{
    // Run the SaltyEngine with default Scene 0
    SaltyEngine::Engine::Instance().Run();
}