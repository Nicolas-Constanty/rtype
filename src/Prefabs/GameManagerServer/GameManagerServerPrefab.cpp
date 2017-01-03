//
// Created by veyrie_f on 29/12/16.
//

#include <Rtype/Game/Client/GameGUILives.hpp>
#include <Common/Flags.hpp>
#include "Rtype/Game/Client/GameGUIBeam.hpp"
#include "Rtype/Game/Client/GameClientObject.hpp"
#include "Prefabs/GameManagerServer/GameManagerServerPrefab.hpp"
#include "Rtype/Game/Client/GameManager.hpp"

GameManagerServerPrefab::GameManagerServerPrefab() : GameObject("GameManagerServer", SaltyEngine::Layer::Tag::GameManager)
{
    SetName("GameManager");
    Flags   flags;
    uint16_t port;
    size_t max;
    uint32_t secret;
    std::string level;

    flags.Var(port, 'p', "port", uint16_t(4242), "The port on which the room server will be binded", "Room port");
    flags.Var(max, 'm', "max", size_t(2), "The maximum amount of players that are allowed to join the room server", "Maximum amount of players");
    flags.Var(secret, 's', "secret", uint32_t(0), "The secret password of the room", "Secret password");
    flags.Var(level, 'l', "level", std::string("scene2Server"), "The ID of the level to load", "Level id");

    flags.Parse(SaltyEngine::Engine::Instance().GetArgc(), (char **)SaltyEngine::Engine::Instance().GetArgv());
    AddComponent<Rtype::Game::Server::GameServerObject>(port, max > 4 ? 4 : max, secret, level);
    AddComponent<GameManager>();
    *SaltyEngine::Engine::Instance().GetCurrentScene() << this;

//    const SaltyEngine::Engine &engine = SaltyEngine::Engine::Instance();
//    const SaltyEngine::Vector2ui size = engine.GetSize();
//
//    SaltyEngine::GameObject     *guiGameBeam = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
//    guiGameBeam->SetName("GUIBeam");
//    guiGameBeam->AddComponent<GameGUIBeam>();
//    SaltyEngine::SFML::SpriteRenderer *sprr = guiGameBeam->GetComponent<SaltyEngine::SFML::SpriteRenderer>();
//    guiGameBeam->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
//    guiGameBeam->transform.SetPosition(size.x / 2,
//                                       size.y - ((sprr) ? (sprr->GetSprite()->GetRect()->_height / 1.5f) : 0));
//
//    SaltyEngine::GameObject     *guiGameHighscore = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
//    guiGameHighscore->SetName("GUIHighscore");
//    guiGameHighscore->AddComponent<GameGUIHighscore>();
//    guiGameHighscore->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
//    guiGameHighscore->transform.SetPosition(static_cast<float>(size.x / 1.2), guiGameBeam->transform.GetPosition().y);
//
//    SaltyEngine::GameObject     *victoryScreen = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
//    victoryScreen->SetName("EndScreen");
//    victoryScreen->AddComponent<EndScreen>();
//    victoryScreen->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
//    victoryScreen->transform.SetPosition(size.x / 2, static_cast<float>(size.y / 2.3));
//    transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
//
//    SaltyEngine::GameObject     *guiLives = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
//    guiLives->SetName("GUILives");
//    guiLives->AddComponent<GameGUILives>();
//    guiLives->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
//    guiLives->transform.SetPosition(static_cast<float>(100), guiGameBeam->transform.GetPosition().y);
//
//
//    // on set le button de fin
//    SaltyEngine::GameObject *launch_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
//    launch_button->SetName("QUITGameButton");
//    SaltyEngine::GUI::SFML::Button *b = launch_button->AddComponent<SaltyEngine::GUI::SFML::Button>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button"),
//                                                                                                    SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over"));
//
//    launch_button->transform.SetParent(&transform);
//    launch_button->transform.SetPosition(size.x / 2, victoryScreen->transform.GetPosition().y + 100);
//    launch_button->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
//    b->onClick.AddListener("LoadRoom", [](){
//        SaltyEngine::Engine::Instance().LoadScene("sceneRoom");
//    });
}

GameManagerServerPrefab::~GameManagerServerPrefab()
{
}

PREF_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new GameManagerServerPrefab();
}