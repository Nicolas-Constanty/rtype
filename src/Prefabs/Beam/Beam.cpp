//
// Created by gouet_v on 12/15/16.
//

#include <SaltyEngine/SFML/Animation.hpp>
#include "Prefabs/Beam/Beam.hpp"
#include "Prefabs/Beam/BeamController.hpp"
#include "SaltyEngine/SFML.hpp"

Beam::Beam() : GameObject("Beam", SaltyEngine::Layer::Tag::Untagged) {
   // AddComponent<::SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Player/Player1"), ::SaltyEngine::Layout::normal);
    AddComponent<BeamController>();
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Laser/loading1"), SaltyEngine::Layout::normal);
    SaltyEngine::SFML::Animation *animation = this->AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
//        SaltyEngine::SFML::Animation *animation = beam->GetComponent<SaltyEngine::SFML::Animation>();
    animation->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Laser/loading"), "Loading");
    animation->Play("Loading");
}

Beam::~Beam() {
}

PREF_EXPORT  SaltyEngine::Object const*GetObjectPrefab()
{
    return new Beam();
}
