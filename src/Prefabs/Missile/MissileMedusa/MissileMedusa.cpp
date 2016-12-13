#include "Prefabs/Missile/MissileMedusa/MissileMedusa.hpp"
#include "Prefabs/Missile/MissileController.hpp"
#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/Animation.hpp"

MissileMedusa::MissileMedusa() : GameObject("MissileMedusa")
{
	AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("missilemedusa"), SaltyEngine::Layout::normal);
	AddComponent < SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
	SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MissileMedusa/Bullet1"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MissileMedusa/Bullet2"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MissileMedusa/Bullet3"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MissileMedusa/Bullet4"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MissileMedusa/Bullet5"));
	clip->SetFrameRate(5);
	GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Shoot");
	AddComponent<MissileController>();
}

MissileMedusa::~MissileMedusa()
{
}

MISSILEMEDUSA_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new MissileMedusa();
}
