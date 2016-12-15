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
    SaltyEngine::SFML::AnimationClip *clip;

    // Walking clip
    clip = new SaltyEngine::SFML::AnimationClip();
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion1"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion2"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion3"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion4"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion5"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion6"));
    clip->SetFrameRate(16);
    GetComponent<SaltyEngine::SFML::Animation >()->AddClip(clip, "Explode");

    AddComponent<ExplosionController>();
}

ExplosionBasic::~ExplosionBasic()
{
}

SaltyEngine::Object const*GetObjectPrefab()
{
	return new ExplosionBasic();
}