//
// Created by veyrie_f on 29/12/16.
//

#include "Rtype/Game/Client/GameGUIBeam.hpp"
#include "Rtype/Game/Client/GameClientObject.hpp"
#include "Prefabs/GameManager/GameManagerPrefab.hpp"
#include "Rtype/Game/Client/GameManager.hpp"

GameManagerPrefab::GameManagerPrefab() : GameObject("GameManager", SaltyEngine::Layer::Tag::GameManager)
{
    AddComponent<GameManager>();
    AddComponent<Rtype::Game::Client::GameClientObject>("127.0.0.1", 4242, 0);

    const SaltyEngine::Engine &engine = SaltyEngine::Engine::Instance();
    const SaltyEngine::Vector2ui size = engine.GetSize();

    SaltyEngine::GameObject     *guiGameBeam = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
    guiGameBeam->SetName("GUIBeam");
    guiGameBeam->AddComponent<GameGUIBeam>();
    SaltyEngine::SFML::SpriteRenderer *sprr = guiGameBeam->GetComponent<SaltyEngine::SFML::SpriteRenderer>();
    guiGameBeam->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    guiGameBeam->transform.SetPosition(size.x / 2,
                                       size.y - ((sprr) ? (sprr->GetSprite()->GetRect()->_height) : 0));

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

//    SaltyEngine::GameObject     *buttonEnd = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
//    buttonEnd->SetName("EndScreen");
//    victoryScreen->AddComponent<EndScreen>();
//    victoryScreen->transform.SetPosition(size.x / 2, static_cast<float>(size.y / 2.3));
}

GameManagerPrefab::~GameManagerPrefab()
{
}

LIB_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new GameManagerPrefab();
}