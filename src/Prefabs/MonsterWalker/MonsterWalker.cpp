#include "Prefabs/MonsterWalker/MonsterWalker.hpp"
#include "Prefabs/MonsterWalker/MonsterWalkerController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/Animation.hpp"

/**
 * @brief You can add your properties here
 */
MonsterWalker::MonsterWalker() : GameObject("MonsterWalker")
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Walker1"), SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
    SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();

    // Walking clip
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Walker1"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Walker2"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Walker3"));
    clip->SetFrameRate(5);
    GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Walk");

    // Jumping clip
    clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Jump1"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Jump2"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Jump3"));
    clip->SetFrameRate(5);
    GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Jump");

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