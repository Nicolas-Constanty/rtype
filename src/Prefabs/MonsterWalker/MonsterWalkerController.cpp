#include "Prefabs/Missile/MissileController.hpp"
#include "Prefabs/MonsterWalker/MonsterWalkerController.hpp"
#include "SaltyEngine/SFML.hpp"

MonsterWalkerController::MonsterWalkerController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour(obj)
{
    m_health = 1;
}


MonsterWalkerController::~MonsterWalkerController()
{
}

void MonsterWalkerController::Start()
{
	m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
}

void MonsterWalkerController::Update()
{
	m_currDelay -= SaltyEngine::SaltyEngine::Instance().GetDeltaTime();

	if (m_currDelay <= 0)
	{
        m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
        SaltyEngine::GameObject *missile = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("MissileMedusa", this->gameObject->transform.position);
        if (missile) {
            MissileController *missileController = missile->GetComponent<MissileController>();
            if (missileController != nullptr) {
                missileController->SetTarget(SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::Player));
            }
            *Singleton<::SaltyEngine::SaltyEngine>::Instance().GetCurrentScene() << missile;
        }
	}
	this->gameObject->transform.Translate(-gameObject->transform.right() * SaltyEngine::SaltyEngine::Instance().GetDeltaTime() * m_vel);
}

void MonsterWalkerController::Die() const
{
    SaltyEngine::Instantiate("ExplosionMonster", this->gameObject->transform.position);
	SaltyEngine::Object::Destroy(this->gameObject);
}

void MonsterWalkerController::TakeDamage(int amount)
{
	AGenericController::TakeDamage(amount);

	if (m_health <= 0 && !m_isDead)
	{
		Die();
		m_isDead = true;
	}
}

void MonsterWalkerController::OnCollisionEnter(SaltyEngine::ICollider *col)
{
    if (col != nullptr)
    {
        SaltyEngine::SFML::BoxCollider2D *c = dynamic_cast<SaltyEngine::SFML::BoxCollider2D*>(col);
        if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::BulletPlayer)
        {
            TakeDamage(1);
        }
    }
}