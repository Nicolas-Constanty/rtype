#include <Prefabs/PositionReplicator/PositionReplicator.hpp>
#include "Prefabs/MonsterFlying/MonsterFlying.hpp"
#include "Prefabs/MonsterFlying/MonsterFlyingController.hpp"

/**
 * @brief You can add your properties here
 */
MonsterFlying::MonsterFlying() : GameObject("MonsterFlying", SaltyEngine::Layer::Tag::Enemy)
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterFlying/FlyR1"), SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);

    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("MonsterFlying/FlyLeft"), "FlyLeft");

    AddComponent<MonsterFlyingController>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
    AddComponent<PositionReplicator>();
}

MonsterFlying::~MonsterFlying()
{
}

LIB_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
	return new MonsterFlying();
}