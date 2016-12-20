#include "Prefabs/{{Prefab}}/{{Prefab}}.hpp"
#include "Prefabs/{{Prefab}}/{{Prefab}}Controller.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/Animation.hpp"

/**
 * \brief You can add your properties here
 */
{{Prefab}}::{{Prefab}}() : GameObject("{{Prefab}}", SaltyEngine::Layer::Tag::Untagged)
{
    AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("{{Prefab}}/{{Prefab}}1"), SaltyEngine::Layout::normal);
    AddComponent < SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
    GetComponent<SaltyEngine::SFML::Animation>()->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("{{Prefab}}/Walk"), "Walk");

    AddComponent<{{Prefab}}Controller>();
    AddComponent<SaltyEngine::SFML::BoxCollider2D>();
}

{{Prefab}}::~{{Prefab}}()
{
}

SaltyEngine::Object const*GetObjectPrefab()
{
    return new {{Prefab}}();
}