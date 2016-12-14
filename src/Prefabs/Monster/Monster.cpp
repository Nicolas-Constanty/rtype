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
    SaltyEngine::SFML::AnimationClip *clip = new SaltyEngine::SFML::AnimationClip();
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Monster/Monster1"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Monster/Monster2"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Monster/Monster3"));
    clip->SetFrameRate(5);
    GetComponent<SaltyEngine::SFML::Animation >()->AddClip(clip, "Walk");

    AddComponent<MonsterController>();
    AddComponent<SaltyEngine::SFML::BoxCollider2D>();
}

Monster::~Monster()
{
}

MONSTER_API SaltyEngine::Object const*GetObjectPrefab()
{
    return new Monster();
}