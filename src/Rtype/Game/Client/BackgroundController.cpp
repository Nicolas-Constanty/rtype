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
    SaltyEngine::SFML::Renderer *renderer = static_cast<SaltyEngine::SFML::Renderer*>(Singleton<SaltyEngine::Engine>::Instance().GetRenderer());
    if (renderer == nullptr) {
        return;
    }
    sf::Vector2u size = renderer->GetRenderWindow()->getSize();
    windowSize = SaltyEngine::Vector2i(size.x, size.y);
    m_start = windowSize.x / 2;
    m_end = windowSize.x + windowSize.x / 2;
    bg1->transform.position.x = m_start;
    bg2->transform.position.x = m_end;
    bg1->transform.position.y = windowSize.y / 2;
    bg2->transform.position.y = windowSize.y / 2;
}

void BackgroundController::FixedUpdate() {
    bg1->transform.position.x -= m_speed;
    bg2->transform.position.x -= m_speed;
    if (bg1->transform.position.x < -m_start) {
        bg1->transform.position.x = m_end;
    }
    if (bg2->transform.position.x < -m_start) {
        bg2->transform.position.x = m_end;
    }
}