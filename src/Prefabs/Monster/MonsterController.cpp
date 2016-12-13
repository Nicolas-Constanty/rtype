#include "Prefabs/Missile/MissileController.hpp"
#include "Prefabs/Monster/MonsterController.hpp"
#include "SaltyEngine/SFML.hpp"

MonsterController::MonsterController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour(obj)
{
    m_health = 1;
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
        }
	}
	this->gameObject->transform.Translate(-gameObject->transform.right() * SaltyEngine::SaltyEngine::Instance().GetDeltaTime() * m_vel);
}

void MonsterController::Die() const
{
    SaltyEngine::Instantiate("ExplosionMonster", this->gameObject->transform.position);
	SaltyEngine::Object::Destroy(this->gameObject);
    std::cout << "Ouch" << std::endl;
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
    if (col != nullptr)
    {
        SaltyEngine::SFML::BoxCollider2D *c = dynamic_cast<SaltyEngine::SFML::BoxCollider2D*>(col);
        if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::BulletPlayer)
        {
            TakeDamage(1);
        }
    }
}