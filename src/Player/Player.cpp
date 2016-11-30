#include "Player/Player.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/Debug.hpp"
#include "Player/PlayerController.hpp"
//#include "SaltyEngine/SFML/Sprite.hpp"

Player::Player() : GameObject("Player")
{
	//SaltyEngine::SFML::Texture *texture = new SaltyEngine::SFML::Texture();
	//if (!texture->loadFromFile("../../Assets/Textures/Image.png"))
	//{
	//	SaltyEngine::Debug::PrintError("Failed to load texture");
	//}
	//else
	//{
	//	SaltyEngine::SFML::Sprite *spr = new SaltyEngine::SFML::Sprite(texture);
	//}
	this->AddComponent<SaltyEngine::PlayerController>();
}


Player::~Player()
{
}

PLAYER_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new Player();
}