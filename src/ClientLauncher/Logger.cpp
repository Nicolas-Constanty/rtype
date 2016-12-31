//
// Created by veyrie_f on 29/12/16.
//

#include "ClientLauncher/Logger.hpp"
#include "ClientLauncher/LoggerController.hpp"
#include "RoomNetworkSaltyEngine/RoomNetworkManager.hpp"

Logger::Logger() : GameObject("Logger")
{
    sf::Font *font = SaltyEngine::SFML::AssetManager::Instance().GetFont("SFSquareHead");
    const SaltyEngine::Engine &engine = SaltyEngine::Engine::Instance();

    SaltyEngine::GameObject *text_box = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    SaltyEngine::GUI::SFML::Label *l = text_box->AddComponent<SaltyEngine::GUI::SFML::Label>("Enter your pseudo : ", 40, font);
    text_box->AddComponent<SaltyEngine::GUI::SFML::TextBox>(l, sf::Vector2f(256.0f, 50.0f), 50, font, sf::Color::White, sf::Color(0x246b9cff), sf::Color(0xbcdbe9ff), 4, 7);
    text_box->SetName("TextBox");
    text_box->transform.SetParent(&transform);
    text_box->transform.SetPosition(0, -130.0f);
    text_box->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));

    SaltyEngine::GameObject *launch_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    launch_button->AddComponent<LoggerController>();
    launch_button->AddComponent<RoomNetworkManager>("127.0.0.1", 4242);
    launch_button->AddComponent<SaltyEngine::GUI::SFML::Label>("START", 54, font);
    launch_button->SetName("LaunchButton");
    SaltyEngine::GUI::SFML::Button *b = launch_button->AddComponent<SaltyEngine::GUI::SFML::Button>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button"),
                                                 SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over"));

    launch_button->transform.SetParent(&transform);
    launch_button->transform.SetPosition(0, 80.0f);
    launch_button->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));

    SaltyEngine::GameObject *background_animation = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    background_animation->SetName("background");
    background_animation->AddComponent<SaltyEngine::SFML::SpriteRenderer>(nullptr, ::SaltyEngine::Layout::normal);
    background_animation->AddComponent<SaltyEngine::SFML::Animation>();
    background_animation->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    background_animation->transform.SetParent(&transform);

    transform.SetPosition(engine.GetSize().x / 2, engine.GetSize().y / 2);
}

Logger::~Logger()
{
}

LIB_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new Logger();
}