#include "SaltyEngine/SFML/Animation.hpp"
#include "Prefabs/Missile/LaserSpiral/LaserSpiral.hpp"
#include "Prefabs/Missile/LaserSpiral/LaserSpiralController.hpp"

LaserSpiral::LaserSpiral() : GameObject("LaserSpiral", SaltyEngine::Layer::Tag::BulletPlayer) {
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("LaserSpiral/Bullet1"), ::SaltyEngine::Layout::normal);
    AddComponent<LaserSpiralController>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
    AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::ONCE);
    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("LaserSpiral/Shoot"), "Shoot");
}

LaserSpiral::~LaserSpiral() {
}

PREF_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new LaserSpiral();
}
