//
// Created by veyrie_f on 29/12/16.
//

#include "ClientLauncher/LoggerController.hpp"

LoggerController::LoggerController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour("LoggerController", obj)
{
}

LoggerController::~LoggerController()
{
}

SaltyEngine::Component *LoggerController::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new LoggerController(obj);
}