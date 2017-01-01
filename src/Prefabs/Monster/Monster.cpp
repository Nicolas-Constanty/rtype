#include <Prefabs/PositionReplicator/PositionReplicator.hpp>
#include "Prefabs/Monster/Monster.hpp"
#include "Prefabs/Monster/MonsterController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/Animation.hpp"

/**
 * \brief You can add your properties here
 */
Monster::Monster() : GameObject("Monster", SaltyEngine::Layer::Tag::Enemy)
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Monster/Monster1"), SaltyEngine::Layout::normal);
    AddComponent < SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Monster/Walk"), "Walk");

    AddComponent<MonsterController>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
    AddComponent<PositionReplicator>();
}

Monster::~Monster()
{
}

PREF_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new Monster();
}