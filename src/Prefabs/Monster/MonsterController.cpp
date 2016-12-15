#include "Prefabs/Missile/MissileController.hpp"
#include "Prefabs/Monster/MonsterController.hpp"
#include "SaltyEngine/SFML.hpp"

MonsterController::MonsterController(SaltyEngine::GameObject *obj) : AGenericController("MonsterController", obj)
{
    m_health = 3;
}


MonsterController::~MonsterController()
{
}

void MonsterController::Start()
{
	m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
}

void MonsterController::Update()
{
	m_currDelay -= static_cast<float>(SaltyEngine::Engine::Instance().GetDeltaTime());

	if (m_currDelay <= 0)
	{
        m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
        Shot();
	}
    Move();
}

void MonsterController::Move() {
    this->gameObject->transform.Translate(-gameObject->transform.right() * SaltyEngine::Engine::Instance().GetDeltaTime() * m_vel);
}

void MonsterController::Shot() {
    SaltyEngine::GameObject *missile = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("MissileMedusa", this->gameObject->transform.position);
    if (missile) {
        MissileController *missileController = missile->GetComponent<MissileController>();
        if (missileController != nullptr) {
            missileController->SetTarget(SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::Player));
        }
    }
}

void MonsterController::Die() const
{
    SaltyEngine::Instantiate("ExplosionBasic", this->gameObject->transform.position);
	SaltyEngine::Object::Destroy(this->gameObject);
}

void MonsterController::TakeDamage(int amount)
{
	AGenericController::TakeDamage(amount);

	if (m_health <= 0 && !m_isDead)
	{
		Die();
		m_isDead = true;
	}
}

void MonsterController::OnCollisionEnter(SaltyEngine::ICollider *col)
{
//    if (col != nullptr)
//    {
//        SaltyEngine::SFML::BoxCollider2D *c = dynamic_cast<SaltyEngine::SFML::BoxCollider2D*>(col);
//        if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::BulletPlayer)
//        {
//            TakeDamage(1);
//        }
//    }
}