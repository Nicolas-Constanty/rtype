//
// Created by gaspar_q on 11/28/16.
//

#include "SaltyEngine/SFML/Scene.hpp"
#include <SaltyEngine/SFML.hpp>
#include <Rtype/Game/Server/RtypeGameServer.hpp>

int main()
{
    // Create Scene
    SaltyEngine::SFML::Scene *scene(new SaltyEngine::SFML::Scene());

    // Create player
    SaltyEngine::GameObject *serverGame = new SaltyEngine::GameObject("Server");

    serverGame->AddComponent<Rtype::Game::Server::RtypeGameServer>();

//    *scene << serverGame;
//
//    // Push scene int SaltyEngine
//    Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;
//
//    // Run the SaltyEngine with default Scene 0
//    Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
}