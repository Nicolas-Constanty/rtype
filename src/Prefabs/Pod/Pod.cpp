//
// Created by gaspar_q on 12/16/16.
//

#include <Prefabs/Pod/PodController.hpp>
#include <SaltyEngine/SFML/SpriteRenderer.hpp>
#include <Prefabs/PositionReplicator/PositionReplicator.hpp>
#include "Prefabs/Pod/Pod.hpp"

Pod::Pod() :
    SaltyEngine::GameObject("Pod", SaltyEngine::Layer::Tag::Pod)
{
    AddComponent<PodController>();
    AddComponent < SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Nacelle/Nacelle0"), "Nacelle0");
    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Nacelle/Nacelle1"), "Nacelle1");
    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Nacelle/Nacelle2"), "Nacelle2");
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
//    AddComponent<PositionReplicator>();
//    AddComponent<SaltyEngine::AAnimationClip>();
}

Pod::~Pod()
{

}

PREF_EXPORT SaltyEngine::Object const *GetObjectPrefab()
{
    return new Pod();
}