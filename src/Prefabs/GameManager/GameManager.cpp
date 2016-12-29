//
// Created by veyrie_f on 29/12/16.
//

#include "Prefabs/GameManager/GameManager.hpp"
#include "SaltyEngine/SFML.hpp"

GameManager::GameManager(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour("GameManager", obj)
{

}

GameManager::~GameManager()
{

}

void GameManager::Start() {
}

SaltyEngine::Component *GameManager::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new GameManager(obj);
}