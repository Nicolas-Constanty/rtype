//
// Created by gaspar_q on 12/12/16.
//

#include <Prefabs/Mate/MateComponent.hpp>
#include "Prefabs/Mate/Mate.hpp"
#include <SaltyEngine/SFML.hpp>
#include <Prefabs/PodHandler/PodHandler.hpp>
#include <Prefabs/CommonPlayer/CommonPlayerController.hpp>

Mate::Mate() :
    SaltyEngine::GameObject("Mate", SaltyEngine::Layer::Tag::Player)
{
    AddComponent<::SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Player/Player1"), ::SaltyEngine::Layout::normal);
    AddComponent<MateComponent>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
    AddComponent<PodHandler>();
    AddComponent<CommonPlayerController>(3);
}

Mate::~Mate()
{

}

LIB_EXPORT SaltyEngine::Object const *GetObjectPrefab()
{
    return new Mate();
}