#include "Prefabs/MonsterNeunoeil/MonsterNeunoeil.hpp"
#include "Prefabs/MonsterNeunoeil/MonsterNeunoeilController.hpp"

/**
 * @brief You can add your properties here
 */
MonsterNeunoeil::MonsterNeunoeil() : GameObject("MonsterNeunoeil", SaltyEngine::Layer::Tag::Enemy)
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterNeunoeil/open"), SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);

    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("MonsterNeunoeil/EyeOpen"), "EyeOpen");
    GetComponent<SaltyEngine::SFML::Animation >()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("MonsterNeunoeil/EyeClose"), "EyeClose");
    GetComponent<SaltyEngine::SFML::Animation >()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("MonsterNeunoeil/EyeBlink"), "EyeBlink");

    AddComponent<MonsterNeunoeilController>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
}

MonsterNeunoeil::~MonsterNeunoeil()
{
}

SaltyEngine::Object const*GetObjectPrefab()
{
	return new MonsterNeunoeil();
}