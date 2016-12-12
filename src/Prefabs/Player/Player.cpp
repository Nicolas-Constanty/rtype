#include "SaltyEngine/Animation.hpp"
#include "Prefabs/Player/Player.hpp"
#include "Prefabs/Player/PlayerController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"

Player::Player() :
        GameObject("Player", SaltyEngine::Layer::Tag::Player)
{
    std::cout << "PLAYER INSANNNNNCE" << std::endl;
    ::SaltyEngine::SFML::Texture *texture = ::SaltyEngine::SFML::AssetManager::Instance().GetTexture("SpaceShips");
    AddComponent<::SaltyEngine::SFML::SpriteRenderer>(new ::SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(34, 0, 33, 17)), ::SaltyEngine::Layout::normal);
    AddComponent<SaltyEngine::PlayerController>();
    std::cout << "PLAYER instantiate !!" << std::endl;
}


Player::~Player()
{
}

PLAYER_API SaltyEngine::Object const*GetObjectPrefab()
{
    return new Player();
}