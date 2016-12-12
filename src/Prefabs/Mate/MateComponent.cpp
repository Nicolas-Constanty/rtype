//
// Created by gaspar_q on 12/12/16.
//

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
