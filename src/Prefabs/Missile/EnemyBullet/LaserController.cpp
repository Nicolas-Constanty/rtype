#include "Prefabs/Missile/EnemyBullet/EnemyBulletController.hpp"
#include "SaltyEngine/SFML.hpp"

EnemyBulletController::EnemyBulletController(SaltyEngine::GameObject *go) : SaltyEngine::SaltyBehaviour(go)
{
}

void EnemyBulletController::Start() {
    SaltyEngine::Sound::ISound *fire = SaltyEngine::SFML::AssetManager::Instance().GetSound("fire");
    fire->Play();
}

EnemyBulletController::~EnemyBulletController()
{
}

void EnemyBulletController::Update()
{
    gameObject->transform.Translate(gameObject->transform.right() * m_vel * SaltyEngine::SaltyEngine::Instance().GetFixedDeltaTime());
}

void EnemyBulletController::OnCollisionEnter(SaltyEngine::ICollider *col)
{
    SaltyEngine::Debug::PrintSuccess("Enemy bullet hit something");
    std::cout << dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(col)->gameObject << std::endl;
    std::cout << dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(col)->gameObject->GetName() << std::endl;
}