#include "SaltyEngine/SFML/Animation.hpp"
#include "Prefabs/Player/Player.hpp"
#include "Prefabs/Player/PlayerController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include <Prefabs/PodHandler/PodHandler.hpp>

Player::Player() : GameObject("Player", SaltyEngine::Layer::Tag::Player)
{
    AddComponent<::SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Player/Player1"), ::SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::PlayerController>();
    AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
    AddComponent<PodHandler>();
}


Player::~Player()
{
}

SaltyEngine::Object const*GetObjectPrefab()
{
    return new Player();
}