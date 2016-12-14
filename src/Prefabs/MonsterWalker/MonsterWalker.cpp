#include "Prefabs/MonsterWalker/MonsterWalker.hpp"
#include "Prefabs/MonsterWalker/MonsterWalkerController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/Animation.hpp"

/**
 * @brief You can add your properties here
 */
MonsterWalker::MonsterWalker() : GameObject("MonsterWalker", SaltyEngine::Layer::Tag::Enemy)
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Walker1L"), SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
    SaltyEngine::AnimationClip<sf::Vector2i> *clip;

    // Walking clip
    clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Walker1L"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Walker2L"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Walker3L"));
    clip->SetFrameRate(8);
    GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "WalkLeft");

    clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Walker1R"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Walker2R"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Walker3R"));
    clip->SetFrameRate(8);
    GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "WalkRight");

    // Jumping clip
    clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Jump1L"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Jump2L"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Jump3L"));
    clip->SetFrameRate(5);
    GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "JumpLeft");

    clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Jump1R"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Jump2R"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MonsterWalker/Jump3R"));
    clip->SetFrameRate(5);
    GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "JumpRight");

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