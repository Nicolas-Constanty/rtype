//
// Created by wery_a on 10/12/16.
//

#include "Prefabs/Missile/Laser/LaserController.hpp"
#include "SaltyEngine/SFML.hpp"

LaserController::LaserController(SaltyEngine::GameObject *go) : SaltyEngine::SaltyBehaviour(go)
{
}

void LaserController::Start() {
    SaltyEngine::Sound::ISound *fire = SaltyEngine::SFML::AssetManager::Instance().GetSound("fire");
    fire->Play();
}

LaserController::~LaserController()
{
}

void LaserController::Update()
{
    gameObject->transform.Translate(gameObject->transform.right() * m_vel * SaltyEngine::SaltyEngine::Instance().GetFixedDeltaTime());
}

void LaserController::OnCollisionEnter(SaltyEngine::ICollider *col)
{
    SaltyEngine::Debug::PrintSuccess("Laser hit something");
    std::cout << dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(col)->gameObject << std::endl;
    std::cout << dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(col)->gameObject->GetName() << std::endl;
}