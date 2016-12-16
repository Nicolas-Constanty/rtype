//
// Created by gaspar_q on 12/16/16.
//

#include <Prefabs/Pod/PodController.hpp>
#include "Prefabs/Pod/Pod.hpp"

Pod::Pod() :
    SaltyEngine::GameObject("Pod", SaltyEngine::Layer::Tag::Player)
{
    AddComponent<PodController>();
//    AddComponent<SaltyEngine::AAnimationClip>();
}

Pod::~Pod()
{

}

SaltyEngine::Object const *GetObjectPrefab()
{
    return new Pod();
}