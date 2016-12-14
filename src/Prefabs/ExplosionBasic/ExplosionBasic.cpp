#include "Prefabs/ExplosionBasic/ExplosionBasic.hpp"
#include "Prefabs/ExplosionBasic/ExplosionController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/Animation.hpp"

/**
 * @brief You can add your properties here
 */
ExplosionBasic::ExplosionBasic() : GameObject("ExplosionBasic")
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion1"), SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::ONCE);
    SaltyEngine::AnimationClip<sf::Vector2i> *clip;

    // Walking clip
    clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion1"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion2"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion3"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion4"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion5"));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite("ExplosionBasic/explosion6"));
    clip->SetFrameRate(16);
    GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Explode");

    AddComponent<ExplosionController>();
}

ExplosionBasic::~ExplosionBasic()
{
}

EXPLOSIONBASIC_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new ExplosionBasic();
}