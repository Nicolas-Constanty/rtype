//
// Created by gaspar_q on 12/12/16.
//

#include <Prefabs/Mate/MateComponent.hpp>
#include "Prefabs/Mate/Mate.hpp"
#include <SaltyEngine/SFML.hpp>

Mate::Mate() :
    SaltyEngine::GameObject("Mate", SaltyEngine::Layer::Tag::Player)
{
    AddComponent<::SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Player/Player1"), ::SaltyEngine::Layout::normal);
    AddComponent<MateComponent>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
}

Mate::~Mate()
{

}

SaltyEngine::Object const *GetObjectPrefab()
{
    return new Mate();
}