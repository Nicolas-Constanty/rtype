#include "Prefabs/MonsterWalker/MonsterWalker.hpp"
#include "Prefabs/MonsterWalker/MonsterWalkerController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/Animation.hpp"

/**
 * @brief You can add your properties here
 */
MonsterWalker::MonsterWalker() : GameObject("MonsterWalker", SaltyEngine::Layer::Tag::Enemy)
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/WalkL1"), SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);

    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("MonsterWalker/WalkLeft"), "WalkLeft");
    GetComponent<SaltyEngine::SFML::Animation >()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("MonsterWalker/WalkRight"), "WalkRight");
    GetComponent<SaltyEngine::SFML::Animation >()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("MonsterWalker/JumpLeft"), "JumpLeft");
    GetComponent<SaltyEngine::SFML::Animation >()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("MonsterWalker/JumpRight"), "JumpRight");

    AddComponent<MonsterWalkerController>();
    AddComponent<SaltyEngine::SFML::BoxCollider2D>();
}

MonsterWalker::~MonsterWalker()
{
}

MONSTERWALKER_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new MonsterWalker();
}