#include "SaltyEngine/Animation.hpp"
#include "Prefabs/Player/Player.hpp"
#include "Prefabs/Player/PlayerController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"

Player::Player() : GameObject("Player", SaltyEngine::Layer::Tag::Player)
{
    AddComponent<SaltyEngine::PlayerController>();
}


Player::~Player()
{
}

PLAYER_API SaltyEngine::Object const*GetObjectPrefab()
{
    return new Player();
}