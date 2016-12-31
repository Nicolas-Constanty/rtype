//
// Created by veyrie_f on 29/12/16.
//

#include "RoomNetworkSaltyEngine/RoomNetworkManager.hpp"
#include "ClientLauncher/LoggerController.hpp"
#include "SaltyEngine/SFML.hpp"

LoggerController::LoggerController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour("LoggerController", obj)
{

}

LoggerController::~LoggerController()
{

}

void LoggerController::Start() {
    m_textBox = SaltyEngine::GameObject::Find("TextBox");
    m_buttonSubmit = SaltyEngine::GameObject::Find("LaunchButton");
    m_submit = m_buttonSubmit->GetComponent<SaltyEngine::GUI::SFML::Button>();
    m_text = m_textBox->GetComponent<SaltyEngine::GUI::SFML::TextBox>();
    m_buttonSubmit->GetComponent<RoomNetworkManager>()->GetNetworkManager()->SetTransitionNetworkManager(this);

    m_submit->onClick.AddListener("Login", [this]()
                           {
                               m_buttonSubmit->GetComponent<RoomNetworkManager>()->SendAuthenticate(m_text->GetText());
                           }
    );

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

void LoggerController::onGetAUTHENTICATE(AUTHENTICATEPackageRoom const &)
{
    SaltyEngine::Engine::Instance().LoadScene("MenuRoom");
}

void LoggerController::onGetCREATE(CREATEPackageRoom const &)
{

}

void LoggerController::onGetJOIN(JOINPackageRoom const &)
{

}

void LoggerController::onGetQUIT(QUITPackageRoom const &)
{

}

void LoggerController::onGetPLUGGED(PLUGGEDPackageRoom const &)
{

}

void LoggerController::onGetSWAP(SWAPPackageRoom const &)
{

}

void LoggerController::onGetGET(GETPackageRoom const &)
{

}

void LoggerController::onGetFAILURE(FAILUREPackageRoom const &)
{

}

void LoggerController::onGetLAUNCH(LAUNCHPackageRoom const &)
{

}

void LoggerController::onGetDELETE(DELETEPackageRoom const &)
{

}

void LoggerController::onGetCHAT(CHATPackageRoom const &)
{

}
