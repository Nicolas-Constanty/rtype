//
// Created by gaspar_q on 12/12/16.
//

#include <SaltyEngine/SFML.hpp>
#include "Prefabs/Mate/MateComponent.hpp"

MateComponent::MateComponent(SaltyEngine::GameObject * const object) :
        SaltyEngine::SaltyBehaviour("MateComponent", object)
{

}

MateComponent::MateComponent(const std::string &name, SaltyEngine::GameObject *const gamObj) :
        SaltyBehaviour(name, gamObj)
{

}

MateComponent::~MateComponent()
{

}

void MateComponent::Start()
{
    std::cout << "START MATE COMPONENT " << std::endl;
    ::SaltyEngine::SFML::Texture *texture = ::SaltyEngine::SFML::AssetManager::Instance().GetTexture("SpaceShips");
    gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(new ::SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(34, 0, 33, 17)), ::SaltyEngine::Layout::normal);
}

SaltyEngine::Component *MateComponent::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new MateComponent(obj);
}
