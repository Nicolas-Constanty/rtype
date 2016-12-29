//
// Created by veyrie_f on 29/12/16.
//

#include "Rtype/Game/Client/GameClientObject.hpp"
#include "Prefabs/GameManager/GameManagerPrefab.hpp"
#include "Prefabs/GameManager/GameManager.hpp"

GameManagerPrefab::GameManagerPrefab() : GameObject("GameManager", SaltyEngine::Layer::Tag::GameManager)
{
    AddComponent<GameManager>();
    AddComponent<Rtype::Game::Client::GameClientObject>("127.0.0.1", 4242, 0);
}

GameManagerPrefab::~GameManagerPrefab()
{
}

LIB_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new GameManagerPrefab();
}