//
// Created by veyrie_f on 29/12/16.
//

#include <Common/Flags.hpp>
#include "RoomNetworkSaltyEngine/RoomNetworkManager.hpp"
#include "ClientLauncher/LoggerController.hpp"
#include "SaltyEngine/SFML.hpp"

LoggerController::LoggerController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour("LoggerController", obj)
{

}

LoggerController::~LoggerController()
{
    std::cout << "delete LoggerController" << std::endl;
//    if (m_roomNetworkManager->GetComponent<RoomNetworkManager>())
//        m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetNetworkManager()->SetTransitionNetworkManager(NULL);
}

void LoggerController::Start() {
    sf::Font *font = SaltyEngine::SFML::AssetManager::Instance().GetFont("SFSquareHead");
    const SaltyEngine::Engine &engine = SaltyEngine::Engine::Instance();

    SaltyEngine::GameObject *text_box = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    SaltyEngine::GUI::SFML::Label *l = text_box->AddComponent<SaltyEngine::GUI::SFML::Label>("Enter your pseudo : ", 40, font);
    text_box->AddComponent<SaltyEngine::GUI::SFML::TextBox>(l, sf::Vector2f(256.0f, 50.0f), 50, font, sf::Color::White, sf::Color(0x246b9cff), sf::Color(0xbcdbe9ff), 4, 7);
    text_box->SetName("TextBox");
    text_box->transform.SetParent(gameObject->transform.GetParent());
    text_box->transform.SetPosition(0, -130.0f);
    text_box->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));

    Flags flags;

    std::string	ip;
    uint16_t port;
    std::string map;
    uint32_t secret;
    flags.Reset();
    flags.Var(ip, 'h', "host", std::string("127.0.0.1"), "The host to which connect", "Game host");
    flags.Var(port, 'p', "port", uint16_t(4242), "The port to which connect", "Game port");
    flags.Var(map, 'l', "level", std::string("sceneConnection"), "The level of the game server", "Game level");
    flags.Var(secret, 's', "secret", uint32_t(0), "The secret code of the game server", "Game secret");
    flags.Parse(SaltyEngine::Engine::Instance().GetArgc(), (char **)SaltyEngine::Engine::Instance().GetArgv());

    SaltyEngine::GameObject *launch_button = SaltyEngine::GameObject::Find("LaunchButton");
    launch_button->AddComponent<SaltyEngine::GUI::SFML::Label>("START", 54, font);
    launch_button->AddComponent<SaltyEngine::GUI::SFML::Button>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button"),
                                                                SaltyEngine::SFML::AssetManager::Instance().GetSprite("GUI/launch_button_over"));
    launch_button->transform.SetPosition(0, 80.0f);
    launch_button->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));

    SaltyEngine::GameObject *tcp_connector = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    tcp_connector->SetName("RoomNetworkManager");
    tcp_connector->AddComponent<RoomNetworkManager>(ip, port);
    SaltyEngine::Object::DontDestroyOnLoad(tcp_connector);

    SaltyEngine::GameObject *background_animation = dynamic_cast<SaltyEngine::GameObject *>(SaltyEngine::Instantiate());
    background_animation->SetName("background");
    background_animation->AddComponent<SaltyEngine::SFML::SpriteRenderer>(nullptr, ::SaltyEngine::Layout::normal);
    background_animation->AddComponent<SaltyEngine::SFML::Animation>();
    background_animation->transform.SetLocalScale(SaltyEngine::Vector2(2, 2));
    background_animation->transform.SetParent(gameObject->transform.GetParent());

    gameObject->transform.GetParent()->SetPosition(engine.GetSize().x / 2, engine.GetSize().y / 2);

    m_textBox = SaltyEngine::GameObject::Find("TextBox");
    m_buttonSubmit = SaltyEngine::GameObject::Find("LaunchButton");
    m_roomNetworkManager = SaltyEngine::GameObject::Find("RoomNetworkManager");
    m_submit = m_buttonSubmit->GetComponent<SaltyEngine::GUI::SFML::Button>();
    m_text = m_textBox->GetComponent<SaltyEngine::GUI::SFML::TextBox>();
    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetNetworkManager()->SetTransitionNetworkManager(this);

    m_submit->onClick.AddListener("Login", [this]()
                           {
                               m_roomNetworkManager->GetComponent<RoomNetworkManager>()->SendAuthenticate(m_text->GetText());
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
//    Debug::PrintSuccess("Mouse Enter");
}

void LoggerController::OnMouseOver() {
    //Debug::PrintInfo("Mouse Over");
}

void LoggerController::OnMouseExit() {
//    Debug::PrintSuccess("Mouse Exit");
}

void LoggerController::onGetAUTHENTICATE(AUTHENTICATEPackageRoom const &)
{
    m_roomNetworkManager->GetComponent<RoomNetworkManager>()->GetNetworkManager()->SetTransitionNetworkManager(NULL);
//    SaltyEngine::Engine::Instance().LoadScene("scene2");
    SaltyEngine::Engine::Instance().LoadScene("sceneRoom");
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
