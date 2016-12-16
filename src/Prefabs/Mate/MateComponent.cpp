//
// Created by gaspar_q on 12/12/16.
//

#include <SFML/Audio.hpp>
#include <SaltyEngine/Collider.hpp>
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
}

SaltyEngine::Component *MateComponent::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new MateComponent(obj);
}

void MateComponent::OnCollisionEnter(SaltyEngine::ICollider *collider)
{
    SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(collider);

    if (c)
    {
        std::string middle = "=   Collision called on: " + c->gameObject->GetName() + "   =";
        std::string limit(middle.size(), '=');

        std::cout << limit << std::endl << middle << std::endl << limit << std::endl;
    }
}
