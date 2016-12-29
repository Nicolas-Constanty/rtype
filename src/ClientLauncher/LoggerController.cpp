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

    SaltyEngine::SFML::Animation *animation = gameObject->transform.GetParent()->GetChild(2)->gameObject->GetComponent<SaltyEngine::SFML::Animation>();
    if (animation)
    {
        animation->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("GUI/animation_login"), "anim");
        animation->Play("anim");
        gameObject->transform.GetParent()->SetLocalScale(SaltyEngine::Vector2(1, 1));
    }
}

SaltyEngine::Component *LoggerController::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new LoggerController(obj);
}

void LoggerController::OnMouseEnter() {
    Debug::PrintSuccess("Mouse Enter");
}

void LoggerController::OnMouseOver() {
    //Debug::PrintInfo("Mouse Over");
}

void LoggerController::OnMouseExit() {
    Debug::PrintSuccess("Mouse Exit");
}
