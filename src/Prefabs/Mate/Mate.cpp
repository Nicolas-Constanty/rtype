//
// Created by gaspar_q on 12/12/16.
//

#include <Prefabs/Mate/MateComponent.hpp>
#include "Prefabs/Mate/Mate.hpp"

Mate::Mate() :
    SaltyEngine::GameObject("Mate", SaltyEngine::Layer::Tag::Player)
{
    std::cout << "Instantiating mate" << std::endl;
    AddComponent<MateComponent>();
}

Mate::~Mate()
{

}

PLAYER_API SaltyEngine::Object const *GetObjectPrefab()
{
    return new Mate();
}