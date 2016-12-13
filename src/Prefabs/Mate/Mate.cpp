//
// Created by gaspar_q on 12/12/16.
//

#include <Prefabs/Mate/MateComponent.hpp>
#include "Prefabs/Mate/Mate.hpp"
#include <SaltyEngine/SFML.hpp>

Mate::Mate() :
    SaltyEngine::GameObject("Mate", SaltyEngine::Layer::Tag::Player)
{
    std::cout << "Instantiating mate" << std::endl;
    ::SaltyEngine::SFML::Texture *texture = ::SaltyEngine::SFML::AssetManager::Instance().GetTexture("SpaceShips"); // 34
    AddComponent<::SaltyEngine::SFML::SpriteRenderer>(new ::SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(34, 0, 33, 17)), ::SaltyEngine::Layout::normal);
    AddComponent<MateComponent>();
}

Mate::~Mate()
{

}

PLAYER_API SaltyEngine::Object const *GetObjectPrefab()
{
    return new Mate();
}