//
// Created by veyrie_f on 29/12/16.
//

#include "ClientLauncher/LoggerController.hpp"
#include "SaltyEngine/SFML.hpp"

LoggerController::LoggerController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour("LoggerController", obj)
{
    gameObject->AddComponent<SaltyEngine::GUI::Button>();
}

LoggerController::~LoggerController()
{

}

void LoggerController::Start() {

}

