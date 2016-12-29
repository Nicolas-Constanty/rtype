//
// Created by veyrie_f on 29/12/16.
//

#include "ClientLauncher/Logger.hpp"
#include "ClientLauncher/LoggerController.hpp"

Logger::Logger() : GameObject("Logger")
{
    SaltyEngine::GameObject *launch_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    launch_button->AddComponent<SaltyEngine::GUI::SFML::Label>("START", 54, SaltyEngine::SFML::AssetManager::Instance().GetFont("SFSquareHead"));
    launch_button->AddComponent<LoggerController>();
    SaltyEngine::GUI::SFML::Button *b = launch_button->AddComponent<SaltyEngine::GUI::SFML::Button>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button"),
                                                 SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over"));
    b->onClick.AddListener("SayOuch", [](){ std::cout << "Ouch!!!" << std::endl;});
    launch_button->transform.SetParent(&transform);
    const SaltyEngine::Engine &engine = SaltyEngine::Engine::Instance();
    transform.SetPosition(engine.GetSize().x, engine.GetSize().y + 200);
}

Logger::~Logger()
{
}

LIB_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new Logger();
}