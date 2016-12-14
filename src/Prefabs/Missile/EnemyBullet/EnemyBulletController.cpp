#include "Prefabs/Missile/EnemyBullet/EnemyBulletController.hpp"
#include "SaltyEngine/SFML.hpp"

EnemyBulletController::EnemyBulletController(SaltyEngine::GameObject *go) : SaltyEngine::SaltyBehaviour(go)
{
}

void EnemyBulletController::Start() {
    SaltyEngine::Sound::ISound *fire = SaltyEngine::SFML::AssetManager::Instance().GetSound("fire");
    fire->Play();
    SaltyEngine::GameObject *t = SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::Player);
    if (t)
        gameObject->transform.LookAt(t->transform);
}

EnemyBulletController::~EnemyBulletController()
{
}

void EnemyBulletController::Update()
{
    gameObject->transform.Translate(gameObject->transform.right() * m_vel * SaltyEngine::Engine::Instance().GetFixedDeltaTime());
}

void EnemyBulletController::OnCollisionEnter(SaltyEngine::ICollider *col)
{
    SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(col);
    if (c && c->gameObject->GetTag() == SaltyEngine::Layer::Tag::Destroy)
    {
        SaltyEngine::Object::Destroy(this->gameObject);
    }
}