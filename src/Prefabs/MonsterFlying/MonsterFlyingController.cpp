#include "Prefabs/Missile/MissileController.hpp"
#include "Prefabs/MonsterFlying/MonsterFlyingController.hpp"
#include "SaltyEngine/SFML.hpp"

MonsterFlyingController::MonsterFlyingController(SaltyEngine::GameObject *obj) : AGenericController("MonsterFlyingController", obj)
{
    m_health = 1;
}


MonsterFlyingController::~MonsterFlyingController()
{
}

void MonsterFlyingController::Start()
{
	m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
}

void MonsterFlyingController::Update()
{
	m_currDelay -= static_cast<float>(SaltyEngine::Engine::Instance().GetDeltaTime());

	if (m_currDelay <= 0)
	{
        m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
        Shot();
	}
    Move();
}

void MonsterFlyingController::Move() {
    this->gameObject->transform.Translate(-(gameObject->transform.right() + SaltyEngine::Vector2(0, sin(gameObject->transform.position.x / 100.f)) ) * SaltyEngine::Engine::Instance().GetDeltaTime() * m_vel);
}

void MonsterFlyingController::Shot() {
    SaltyEngine::GameObject *missile = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("EnemyBullet", this->gameObject->transform.position, 180);

    if (missile) {
        MissileController *missileController = missile->GetComponent<MissileController>();
        if (missileController != nullptr) {
            missileController->SetTarget(SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::Player));
        }
    }
}

void MonsterFlyingController::Die() const
{
    SaltyEngine::Instantiate("ExplosionBasic", this->gameObject->transform.position);
	SaltyEngine::Object::Destroy(this->gameObject);
}

void MonsterFlyingController::TakeDamage(int amount) {
    AGenericController::TakeDamage(amount);

    if (m_health <= 0 && !m_isDead) {
        Die();
        m_isDead = true;
    }
}