#include "Prefabs/Missile/MissileNeunoeil/MissileNeunoeil.hpp"
#include "Prefabs/Missile/MissileNeunoeil/MissileNeunoeilController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/Animation.hpp"

/**
 * \brief You can add your properties here
 */
MissileNeunoeil::MissileNeunoeil() : GameObject("MissileNeunoeil", SaltyEngine::Layer::Tag::BulletEnemy)
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterNeunoeil/bullet1"), SaltyEngine::Layout::normal);
    AddComponent < SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("MonsterNeunoeil/bullet"), "Walk");

    AddComponent<MissileNeunoeilController>();
    AddComponent<SaltyEngine::SFML::BoxCollider2D>();
}

MissileNeunoeil::~MissileNeunoeil()
{
}

SaltyEngine::Object const*GetObjectPrefab()
{
    return new MissileNeunoeil();
}