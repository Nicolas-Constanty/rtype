#include "SaltyEngine/SFML/Animation.hpp"
#include "Prefabs/Missile/EnemyBullet/EnemyBullet.hpp"
#include "Prefabs/Missile/EnemyBullet/EnemyBulletController.hpp"
#include "SaltyEngine/SFML.hpp"

EnemyBullet::EnemyBullet() : GameObject("EnemyBullet", SaltyEngine::Layer::Tag::BulletEnemy) {
	AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Missile/Bullet1"), ::SaltyEngine::Layout::normal);
	AddComponent<EnemyBulletController>();
    AddComponent<SaltyEngine::SFML::BoxCollider2D>();

	AddComponent < SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
	SaltyEngine::SFML::AnimationClip *clip = new SaltyEngine::SFML::AnimationClip();
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Missile/Bullet1"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Missile/Bullet2"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Missile/Bullet3"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Missile/Bullet4"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Missile/Bullet5"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Missile/Bullet6"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Missile/Bullet7"));
	clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Missile/Bullet8"));
	clip->SetFrameRate(5);
	GetComponent<SaltyEngine::SFML::Animation >()->AddClip(clip, "Fire");
}

EnemyBullet::~EnemyBullet() {
}

SaltyEngine::Object const*GetObjectPrefab()
{
	return new EnemyBullet();
}
