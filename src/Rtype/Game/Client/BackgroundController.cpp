//
// Created by wery_a on 17/12/16.
//

#include <SaltyEngine/SFML/SpriteRenderer.hpp>
#include "Rtype/Game/Client/BackgroundController.hpp"

BackgroundController::BackgroundController(SaltyEngine::GameObject * const gameObj)
        : SaltyBehaviour("BackgroundController", gameObj) {
    bg1 = static_cast<SaltyEngine::GameObject*>(SaltyEngine::Instantiate());
    bg1->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("background"), ::SaltyEngine::Layout::background);

    bg2 = static_cast<SaltyEngine::GameObject*>(SaltyEngine::Instantiate());
    bg2->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("background"), ::SaltyEngine::Layout::background);

    *Singleton<::SaltyEngine::Engine>::Instance().GetCurrentScene() << bg1;
    *Singleton<::SaltyEngine::Engine>::Instance().GetCurrentScene() << bg2;
}

BackgroundController::~BackgroundController() {

}

void BackgroundController::Start() {
    SaltyEngine::SFML::Renderer *renderer = dynamic_cast<SaltyEngine::SFML::Renderer*>(SaltyEngine::Engine::Instance().GetRenderer());
    if (renderer == nullptr) {
        return;
    }
    windowSize = renderer->GetRealSize();
    m_start = windowSize.x / 2;
    m_end = windowSize.x + windowSize.x / 2;
    bg1->transform.SetPosition(m_start, windowSize.y / 2);
    bg2->transform.SetPosition(m_end, windowSize.y / 2);
}

void BackgroundController::FixedUpdate() {
    float x1 = bg1->transform.GetPosition().x;
    float y1 = bg1->transform.GetPosition().y;
    float x2 = bg2->transform.GetPosition().x;
    float y2 = bg1->transform.GetPosition().y;
//    bg1->transform.position.x -= m_speed;
//    bg2->transform.position.x -= m_speed;
    x1 -= m_speed;
    x2 -= m_speed;
    if (x1 < -m_start) {
        x1 = m_end;
    }
    if (x2 < -m_start) {
        x2 = m_end;
    }
    bg1->transform.SetPosition(x1, y1);
    bg2->transform.SetPosition(x2, y2);

//    if (bg1->transform.position.x < -m_start) {
//        bg1->transform.position.x = m_end;
//    }
//    if (bg2->transform.position.x < -m_start) {
//        bg2->transform.position.x = m_end;
//    }
}