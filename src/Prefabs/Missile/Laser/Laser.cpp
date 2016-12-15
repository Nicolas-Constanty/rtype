#include <SaltyEngine/SFML/Animation.hpp>
#include "Prefabs/Missile/Laser/Laser.hpp"
#include "Prefabs/Missile/Laser/LaserController.hpp"
#include "SaltyEngine/SFML.hpp"

Laser::Laser() : GameObject("Laser", SaltyEngine::Layer::Tag::BulletPlayer) {
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Laser/simple"), ::SaltyEngine::Layout::normal);
    AddComponent<LaserController>();
    AddComponent<SaltyEngine::SFML::BoxCollider2D>();
    AddComponent<SaltyEngine::SFML::Animation>();
}

Laser::~Laser() {
}

SaltyEngine::Object const*GetObjectPrefab()
{
    return new Laser();
}
