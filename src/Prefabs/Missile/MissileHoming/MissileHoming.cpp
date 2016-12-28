#include "Prefabs/Missile/MissileHoming/MissileHoming.hpp"
#include "Prefabs/Missile/MissileHoming/MissileHomingController.hpp"

/**
 * \brief You can add your properties here
 */
MissileHoming::MissileHoming() : GameObject("MissileHoming", SaltyEngine::Layer::Tag::BulletPlayer)
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MissileHoming/Bullet1"), SaltyEngine::Layout::normal);
    AddComponent < SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::PING_PONG);
    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("MissileHoming/Shoot"), "Shoot");

    AddComponent<MissileHomingController>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
}

MissileHoming::~MissileHoming()
{
}

PREF_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new MissileHoming();
}