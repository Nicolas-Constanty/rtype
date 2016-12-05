//
// Created by gaspar_q on 11/28/16.
//

#include <SaltyEngine/SaltyEngine.hpp>
#include <ServerGame/RtypeGameServer.hpp>

int main()
{
    // Create Scene
    SaltyEngine::Scene *scene(new SaltyEngine::Scene());

    // Create player
    SaltyEngine::GameObject *serverGame = new SaltyEngine::GameObject("Server");

    serverGame->AddComponent<Rtype::RtypeGameServer>();

    *scene << serverGame;

    // Push scene int SaltyEngine
    Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;

    // Run the SaltyEngine with default Scene 0
    Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
}