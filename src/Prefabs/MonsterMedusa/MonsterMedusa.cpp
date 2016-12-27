#include "Prefabs/PositionReplicator/PositionReplicator.hpp"
#include "Prefabs/MonsterMedusa/MonsterMedusa.hpp"
#include "Prefabs/MonsterMedusa/MonsterMedusaController.hpp"

/**
 * @brief You can add your properties here
 */
MonsterMedusa::MonsterMedusa() : GameObject("MonsterMedusa", SaltyEngine::Layer::Tag::Enemy)
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterMedusa/Medusa1"), SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);

    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("MonsterMedusa/Fly"), "Fly");

    AddComponent<MonsterMedusaController>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
    AddComponent<PositionReplicator>();
}

MonsterMedusa::~MonsterMedusa()
{
}

LIB_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
	return new MonsterMedusa();
}