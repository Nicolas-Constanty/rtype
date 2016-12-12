#include "Prefabs/Missile/EnemyBullet/EnemyBullet.hpp"
#include "Prefabs/Missile/EnemyBullet/EnemyBulletController.hpp"
#include "SaltyEngine/SFML.hpp"

EnemyBullet::EnemyBullet() : GameObject("EnemyBullet", SaltyEngine::Layer::Tag::BulletEnemy) {
	AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("EnemyBullet"), ::SaltyEngine::Layout::normal);
	AddComponent<EnemyBulletController>();
    AddComponent<SaltyEngine::SFML::BoxCollider2D>();
}

EnemyBullet::~EnemyBullet() {
}

ENEMYBULLET_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new EnemyBullet();
}
