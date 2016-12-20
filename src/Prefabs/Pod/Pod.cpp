//
// Created by gaspar_q on 12/16/16.
//

#include <Prefabs/Pod/PodController.hpp>
#include <SaltyEngine/SFML/SpriteRenderer.hpp>
#include "Prefabs/Pod/Pod.hpp"

Pod::Pod() :
    SaltyEngine::GameObject("Pod", SaltyEngine::Layer::Tag::Player)
{
    AddComponent<PodController>();
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Player/Player1"), ::SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
//    AddComponent<SaltyEngine::AAnimationClip>();
}

Pod::~Pod()
{

}

SaltyEngine::Object const *GetObjectPrefab()
{
    return new Pod();
}