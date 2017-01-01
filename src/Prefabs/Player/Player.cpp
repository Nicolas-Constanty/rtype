#include "SaltyEngine/SFML/Animation.hpp"
#include "Prefabs/Player/Player.hpp"
#include "Prefabs/Player/PlayerController.hpp"
#include "Prefabs/PodHandler/PodHandler.hpp"

Player::Player() : GameObject("Player", SaltyEngine::Layer::Tag::Player)
{
    AddComponent<::SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Player/Player1"), ::SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::PlayerController>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
    AddComponent<PodHandler>();
    AddComponent<CommonPlayerController>(3);
}


Player::~Player()
{
}

PREF_EXPORT SaltyEngine::Object const*GetObjectPrefab()
{
    return new Player();
}