#include "Prefabs/ExplosionBasic/ExplosionBasic.hpp"
#include "Prefabs/ExplosionBasic/ExplosionController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/Animation.hpp"

/**
 * @brief You can add your properties here
 */
ExplosionBasic::ExplosionBasic() : GameObject("ExplosionBasic")
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion1"), SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::ONCE);

    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Explosion/basic"), "Explode");

    AddComponent<ExplosionController>();
}

ExplosionBasic::~ExplosionBasic()
{
}

LIB_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
	return new ExplosionBasic();
}