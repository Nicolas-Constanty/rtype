#include "Prefabs/Missile/Laser/Laser.hpp"
#include "Prefabs/Missile/Laser/LaserController.hpp"
#include "SaltyEngine/SFML.hpp"

Laser::Laser() : GameObject("Laser", SaltyEngine::Layer::Tag::BulletPlayer) {
	SaltyEngine::SFML::Texture *texture = SaltyEngine::SFML::AssetManager::Instance().GetTexture("Laser");
	SaltyEngine::SFML::Sprite *spr = new ::SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(201, 154, 64, 14));
	AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, ::SaltyEngine::Layout::normal);
	AddComponent<LaserController>();
    AddComponent<SaltyEngine::SFML::BoxCollider2D>();
}

Laser::~Laser() {
}

LASER_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new Laser();
}
