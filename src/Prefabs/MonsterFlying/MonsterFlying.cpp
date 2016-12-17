#include "Prefabs/MonsterFlying/MonsterFlying.hpp"
#include "Prefabs/MonsterFlying/MonsterFlyingController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/Animation.hpp"

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
}

MonsterFlying::~MonsterFlying()
{
}

SaltyEngine::Object const*GetObjectPrefab()
{
	return new MonsterFlying();
}