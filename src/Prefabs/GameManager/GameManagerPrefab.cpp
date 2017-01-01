//
// Created by veyrie_f on 29/12/16.
//

#include <Rtype/Game/Client/GameGUILives.hpp>
#include "Rtype/Game/Client/GameGUIBeam.hpp"
#include "Rtype/Game/Client/GameClientObject.hpp"
#include "Prefabs/GameManager/GameManagerPrefab.hpp"
#include "Rtype/Game/Client/GameManager.hpp"

GameManagerPrefab::GameManagerPrefab() : GameObject("GameManager", SaltyEngine::Layer::Tag::GameManager)
{

//    std::string ip = "127.0.0.1";
//    unsigned int port = 4241;
//    unsigned int secret = 0;

    AddComponent<GameManager>();
//    SaltyEngine::GameObject *m_roomNetworkManager = SaltyEngine::GameObject::Find("RoomNetworkManager");

//    if (m_roomNetworkManager) {
//        ip = m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetUDPIP();
//        port = m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetUDPPort();
//        secret = m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetUDPSecret();
//    }

//    AddComponent<Rtype::Game::Client::GameClientObject>(ip, port, secret);

    const SaltyEngine::Engine &engine = SaltyEngine::Engine::Instance();
    const SaltyEngine::Vector2ui size = engine.GetSize();

    SaltyEngine::GameObject     *guiGameBeam = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
    guiGameBeam->SetName("GUIBeam");
    guiGameBeam->AddComponent<GameGUIBeam>();
    SaltyEngine::SFML::SpriteRenderer *sprr = guiGameBeam->GetComponent<SaltyEngine::SFML::SpriteRenderer>();
    guiGameBeam->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    guiGameBeam->transform.SetPosition(size.x / 2,
                                       size.y - ((sprr) ? (sprr->GetSprite()->GetRect()->_height / 1.5f) : 0));

    SaltyEngine::GameObject     *guiGameHighscore = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
    guiGameHighscore->SetName("GUIHighscore");
    guiGameHighscore->AddComponent<GameGUIHighscore>();
    guiGameHighscore->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    guiGameHighscore->transform.SetPosition(static_cast<float>(size.x / 1.2), guiGameBeam->transform.GetPosition().y);

    SaltyEngine::GameObject     *victoryScreen = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
    victoryScreen->SetName("EndScreen");
    victoryScreen->AddComponent<EndScreen>();
    victoryScreen->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    victoryScreen->transform.SetPosition(size.x / 2, static_cast<float>(size.y / 2.3));
    transform.SetLocalScale(SaltyEngine::Vector2(2, 2));

    SaltyEngine::GameObject     *guiLives = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
    guiLives->SetName("GUILives");
    guiLives->AddComponent<GameGUILives>();
    guiLives->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    guiLives->transform.SetPosition(static_cast<float>(100), guiGameBeam->transform.GetPosition().y);


    // on set le button de fin
    SaltyEngine::GameObject *launch_button = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    launch_button->SetName("QUITGameButton");
    SaltyEngine::GUI::SFML::Button *b = launch_button->AddComponent<SaltyEngine::GUI::SFML::Button>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button"),
                                                                                                    SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over"));

    launch_button->transform.SetParent(&transform);
    launch_button->transform.SetPosition(size.x / 2, victoryScreen->transform.GetPosition().y + 100);
    launch_button->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    b->onClick.AddListener("SayOuch", [](){
        std::cout << "Ouch!!!" << std::endl;
        //TODO retour dans la guiRoom
        SaltyEngine::Engine::Instance().Stop();
    });




//    SaltyEngine::GameObject     *buttonEnd = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
//    buttonEnd->SetName("EndScreen");
//    victoryScreen->AddComponent<EndScreen>();
//    victoryScreen->transform.SetPosition(size.x / 2, static_cast<float>(size.y / 2.3));
}

GameManagerPrefab::~GameManagerPrefab()
{
}

PREF_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new GameManagerPrefab();
}