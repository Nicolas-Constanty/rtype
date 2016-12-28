//
// Created by wery_a on 17/12/16.
//

#include <SaltyEngine/SFML/SpriteRenderer.hpp>
#include "Rtype/Game/Client/BackgroundController.hpp"

BackgroundController::BackgroundController(SaltyEngine::GameObject * const gameObj)
        : SaltyBehaviour("BackgroundController", gameObj) {
    m_starfieldFar1 = static_cast<SaltyEngine::GameObject*>(SaltyEngine::Instantiate());
    m_starfieldFar1->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("StarfieldFar"), ::SaltyEngine::Layout::backgroundColor);

    m_starfieldFar2 = static_cast<SaltyEngine::GameObject*>(SaltyEngine::Instantiate());
    m_starfieldFar2->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("StarfieldFar"), ::SaltyEngine::Layout::backgroundColor);

    m_starfieldNear1 = static_cast<SaltyEngine::GameObject*>(SaltyEngine::Instantiate());
    m_starfieldNear1->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("StarfieldNear"), ::SaltyEngine::Layout::backgroundColor);

    m_starfieldNear2 = static_cast<SaltyEngine::GameObject*>(SaltyEngine::Instantiate());
    m_starfieldNear2->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("StarfieldNear"), ::SaltyEngine::Layout::backgroundColor);

    m_background = static_cast<SaltyEngine::GameObject*>(SaltyEngine::Instantiate());
    m_background->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Background"), ::SaltyEngine::Layout::background);
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
    m_starfieldFar1->transform.SetPosition(m_start, windowSize.y / 2);
    m_starfieldFar2->transform.SetPosition(m_end, windowSize.y / 2);
    m_starfieldNear1->transform.SetPosition(m_start, windowSize.y / 2);
    m_starfieldNear2->transform.SetPosition(m_end, windowSize.y / 2);
    m_background->transform.SetPosition(m_start, windowSize.y / 2);
}

void BackgroundController::FixedUpdate() {
    float x1 = m_starfieldFar1->transform.GetPosition().x;
    float y1 = m_starfieldFar1->transform.GetPosition().y;
    float x2 = m_starfieldFar2->transform.GetPosition().x;
    float y2 = m_starfieldFar2->transform.GetPosition().y;

    x1 -= m_speed;
    x2 -= m_speed;
    if (x1 < -m_start) {
        x1 = m_end;
    }
    if (x2 < -m_start) {
        x2 = m_end;
    }
    m_starfieldFar1->transform.SetPosition(x1, y1);
    m_starfieldFar2->transform.SetPosition(x2, y2);

    x1 = m_starfieldNear1->transform.GetPosition().x;
    y1 = m_starfieldNear1->transform.GetPosition().y;
    x2 = m_starfieldNear2->transform.GetPosition().x;
    y2 = m_starfieldNear2->transform.GetPosition().y;

    x1 -= m_speed / 2;
    x2 -= m_speed / 2;
    if (x1 < -m_start) {
        x1 = m_end;
    }
    if (x2 < -m_start) {
        x2 = m_end;
    }
    m_starfieldNear1->transform.SetPosition(x1, y1);
    m_starfieldNear2->transform.SetPosition(x2, y2);
}