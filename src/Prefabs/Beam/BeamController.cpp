//
// Created by gouet_v on 12/15/16.
//

#include "Prefabs/GenericController.hpp"
#include "Prefabs/Beam/Beam.hpp"
#include "Prefabs/Beam/BeamController.hpp"
#include "SaltyEngine/SFML.hpp"

BeamController::BeamController(SaltyEngine::GameObject *go) : SaltyEngine::SaltyBehaviour(go)
{
    soundLoad = SaltyEngine::SFML::AssetManager::Instance().GetSound("Laser/loading");
    soundLoad->SetLoop(true);
}

void BeamController::Start() {
    soundLoad->Play();
}

BeamController::~BeamController()
{
    delete soundLoad;
}
