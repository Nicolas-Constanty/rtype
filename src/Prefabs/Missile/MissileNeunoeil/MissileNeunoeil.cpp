#include "Prefabs/Missile/MissileNeunoeil/MissileNeunoeil.hpp"
#include "Prefabs/Missile/MissileNeunoeil/MissileNeunoeilController.hpp"

/**
 * \brief You can add your properties here
 */
MissileNeunoeil::MissileNeunoeil() : GameObject("MissileNeunoeil", SaltyEngine::Layer::Tag::BulletEnemy)
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterNeunoeil/bullet1"), SaltyEngine::Layout::normal);
    AddComponent < SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("MonsterNeunoeil/bullet"), "Shoot");

    AddComponent<MissileNeunoeilController>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
}

MissileNeunoeil::~MissileNeunoeil()
{
}

PREF_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new MissileNeunoeil();
}