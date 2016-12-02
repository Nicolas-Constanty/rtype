//
// Created by gaspar_q on 11/30/16.
//

#include <ServerGame/Room.hpp>
#include <SaltyEngine/SaltyEngine.hpp>

Rtype::Room::Room()
{

}

Rtype::Room::~Room()
{

}

void Rtype::Room::Start(const uint16_t port)
{
    // Create Scene
    SaltyEngine::Scene *scene(new SaltyEngine::Scene());

    // Create player
    SaltyEngine::GameObject *serverGame = new SaltyEngine::GameObject("Server");

    server = serverGame->AddComponent<Rtype::RtypeGameServer>(port);

    *scene << serverGame;

    // Push scene int SaltyEngine
    Singleton<SaltyEngine::SaltyEngine>::Instance() << scene;
}

void Rtype::Room::Run()
{
    // Run the SaltyEngine with default Scene 0
    Singleton<SaltyEngine::SaltyEngine>::Instance().Run();
}

void Rtype::Room::Stop()
{
    server->Disconnect();
}
