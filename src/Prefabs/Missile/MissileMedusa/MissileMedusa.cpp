#include "Prefabs/Missile/MissileMedusa/MissileMedusa.hpp"
#include "Prefabs/Missile/MissileController.hpp"
#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/SFML/Animation.hpp"

MissileMedusa::MissileMedusa() : GameObject("MissileMedusa")
{
	AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MissileMedusa/Bullet1"), SaltyEngine::Layout::normal);
	AddComponent < SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
	SaltyEngine::SFML::AnimationClip *clip = new SaltyEngine::SFML::AnimationClip();
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MissileMedusa/Bullet1"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MissileMedusa/Bullet2"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MissileMedusa/Bullet3"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MissileMedusa/Bullet4"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("MissileMedusa/Bullet5"));
	clip->SetFrameRate(5);
	GetComponent<SaltyEngine::SFML::Animation >()->AddClip(clip, "Shoot");
	AddComponent<MissileController>();
}

MissileMedusa::~MissileMedusa()
{
}

MISSILEMEDUSA_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new MissileMedusa();
}
