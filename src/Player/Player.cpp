#include "SaltyEngine/SFML/Texture.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "Player/Player.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/Debug.hpp"
#include "Player/PlayerController.hpp"
#include "SaltyEngine/SFML/Button.hpp"

Player::Player() : GameObject("Player")
{
	this->AddComponent<SaltyEngine::PlayerController>();
}


Player::~Player()
{
}

PLAYER_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new Player();
}