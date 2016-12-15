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
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterFlying/Fly1R"), SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
    SaltyEngine::SFML::AnimationClip *clip;

    // Walking clip
    clip = new SaltyEngine::SFML::AnimationClip();
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterFlying/Fly1R"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterFlying/Fly2R"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterFlying/Fly3R"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterFlying/Fly4R"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterFlying/Fly5R"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterFlying/Fly6R"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterFlying/Fly7R"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterFlying/Fly8R"));
    clip->SetFrameRate(8);
    GetComponent<SaltyEngine::SFML::Animation >()->AddClip(clip, "FlyLeft");

    AddComponent<MonsterFlyingController>();
    AddComponent<SaltyEngine::SFML::BoxCollider2D>();
}

MonsterFlying::~MonsterFlying()
{
}

SaltyEngine::Object const*GetObjectPrefab()
{
	return new MonsterFlying();
}