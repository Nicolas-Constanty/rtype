//
// Created by veyrie_f on 29/12/16.
//

#include "ClientLauncher/LoggerController.hpp"
#include "SaltyEngine/SFML.hpp"

LoggerController::LoggerController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour("LoggerController", obj)
{

}

LoggerController::~LoggerController()
{

}

void LoggerController::Start() {
    gameObject->AddComponent<::SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button"), ::SaltyEngine::Layout::normal);
    gameObject->AddComponent<SaltyEngine::GUI::SFML::Button>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button"),
                                                       SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over"));
}

SaltyEngine::Component *LoggerController::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new LoggerController(obj);
}

void LoggerController::OnMouseEnter() {
    Debug::PrintSuccess("Mouse Enter");
}

void LoggerController::OnMouseOver() {
    Debug::PrintInfo("Mouse Over");
}

void LoggerController::OnMouseExit() {
    Debug::PrintSuccess("Mouse Exit");
}
