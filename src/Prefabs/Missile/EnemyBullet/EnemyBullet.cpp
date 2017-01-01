#include "SaltyEngine/SFML.hpp"
#include "Prefabs/Missile/EnemyBullet/EnemyBullet.hpp"
#include "Prefabs/Missile/EnemyBullet/EnemyBulletController.hpp"

EnemyBullet::EnemyBullet() : GameObject("EnemyBullet", SaltyEngine::Layer::Tag::BulletEnemy) {
	AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Missile/Bullet1"), ::SaltyEngine::Layout::normal);
	AddComponent<EnemyBulletController>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();

	AddComponent < SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
	GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Missile/Fire"), "Fire");
}

EnemyBullet::~EnemyBullet() {
}

PREF_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
	return new EnemyBullet();
}
