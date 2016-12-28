#include "SaltyEngine/SFML.hpp"
#include "Prefabs/Missile/MissileMedusa/MissileMedusa.hpp"
#include "Prefabs/Missile/MissileController.hpp"

MissileMedusa::MissileMedusa() : GameObject("MissileMedusa")
{
	AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Missile/Bullet1"), SaltyEngine::Layout::normal);
	AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
	GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Missile/Shoot"), "Shoot");
	AddComponent<MissileController>();
}

MissileMedusa::~MissileMedusa()
{
}

PREF_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
	return new MissileMedusa();
}
