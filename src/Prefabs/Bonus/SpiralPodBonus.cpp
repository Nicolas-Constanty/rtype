//
// Created by gaspar_q on 12/26/16.
//

#include <Prefabs/Bonus/SpiralPodBonus.hpp>
#include <Prefabs/Bonus/SpiralPodBonusController.hpp>

SpiralPodBonus::SpiralPodBonus() :
    SaltyEngine::GameObject("SpiralBonus", SaltyEngine::Layer::Tag::Player)
{
    AddComponent<SpiralPodBonusController>();
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Bonus/SpiralBonus"), ::SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
}

SpiralPodBonus::~SpiralPodBonus()
{

}

PREF_EXPORT SaltyEngine::Object const *GetObjectPrefab()
{
    return new SpiralPodBonus();
}