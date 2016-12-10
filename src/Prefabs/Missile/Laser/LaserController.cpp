//
// Created by wery_a on 10/12/16.
//

#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "Prefabs/Missile/Laser/LaserController.hpp"

LaserController::LaserController(SaltyEngine::GameObject *go) : SaltyEngine::SaltyBehaviour(go)
{
}

void LaserController::Start() {
    SaltyEngine::SFML::Texture *texture = SaltyEngine::SFML::AssetManager::Instance().GetTexture("Laser");
    SaltyEngine::SFML::Sprite *spr = new ::SaltyEngine::SFML::Sprite(texture, new ::SaltyEngine::SFML::Rect(201, 154, 64, 14));
    gameObject->AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, ::SaltyEngine::Layout::normal);
    SaltyEngine::Sound::ISound *fire = SaltyEngine::SFML::AssetManager::Instance().GetSound("fire");
    fire->Play();
}

LaserController::~LaserController()
{
}

void LaserController::Update()
{
    gameObject->transform.Translate(SaltyEngine::Vector(1, 0) * m_vel * SaltyEngine::SaltyEngine::Instance().GetFixedDeltaTime());
}

void LaserController::OnCollisionEnter(SaltyEngine::ICollider *)
{
    SaltyEngine::Debug::PrintSuccess("Laser hit something");
}