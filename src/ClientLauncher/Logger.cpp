//
// Created by veyrie_f on 29/12/16.
//

#include <Common/Flags.hpp>
#include "ClientLauncher/Logger.hpp"
#include "ClientLauncher/LoggerController.hpp"
#include "RoomNetworkSaltyEngine/RoomNetworkManager.hpp"

Logger::Logger() : GameObject("Logger")
{
    const SaltyEngine::Engine &engine = SaltyEngine::Engine::Instance();

    SaltyEngine::GameObject *launch_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    launch_button->SetName("LaunchButton");
    launch_button->AddComponent<LoggerController>();
    launch_button->transform.SetParent(&transform);
//    transform.SetPosition(engine.GetSize().x / 2, engine.GetSize().y / 2);
}

Logger::~Logger()
{
}

PREF_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new Logger();
}