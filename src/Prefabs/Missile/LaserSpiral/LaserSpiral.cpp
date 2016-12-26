#include "SaltyEngine/SFML/Animation.hpp"
#include "Prefabs/Missile/LaserSpiral/LaserSpiral.hpp"
#include "Prefabs/Missile/LaserSpiral/LaserSpiralController.hpp"
#include "SaltyEngine/SFML.hpp"

LaserSpiral::LaserSpiral() : GameObject("LaserSpiral", SaltyEngine::Layer::Tag::BulletPlayer) {
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("LaserSpiral/simple"), ::SaltyEngine::Layout::normal);
    AddComponent<LaserSpiralController>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
    AddComponent<SaltyEngine::SFML::Animation>();
}

LaserSpiral::~LaserSpiral() {
}

SaltyEngine::Object const*GetObjectPrefab()
{
    return new LaserSpiral();
}
