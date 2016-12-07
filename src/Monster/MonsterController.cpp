#include "SaltyEngine/SaltyEngine.hpp"
#include "Monster/MonsterController.hpp"
#include "Missile/MissileController.hpp"

MonsterController::MonsterController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour(obj)
{
	//m_currDelay = m_minShootInterval + ( ((m_maxShootInterval - m_minShootInterval) * rand()) / (RAND_MAX + 1) );
	m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
}


MonsterController::~MonsterController()
{
}

void MonsterController::Start()
{
}

void MonsterController::Update()
{
	m_currDelay -= SaltyEngine::SaltyEngine::Instance().GetDeltaTime();

	if (m_currDelay <= 0)
	{
//		m_currDelay = m_minShootInterval + (((m_maxShootInterval - m_minShootInterval) * rand()) / (RAND_MAX + 1));
        m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
        std::cout << "SHOOT" << std::endl;
        SaltyEngine::GameObject *missile = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("MissileMedusa", this->gameObject->transform.position);
//        MissileController *missileController = missile->GetComponent<MissileController>();
//        if (missileController != nullptr)
//        {
//			// TODO : target player
//            missileController->SetTarget(SaltyEngine::Vector(this->gameObject->transform.position.x * -100, this->gameObject->transform.position.y));
//        }
	}
	this->gameObject->transform.Translate(SaltyEngine::Vector(-1, 0) * SaltyEngine::SaltyEngine::Instance().GetDeltaTime() * m_vel);
}

void MonsterController::Die() const
{
    SaltyEngine::Object::Destroy(this->gameObject);
    SaltyEngine::Instantiate("ExplosionMonster", this->gameObject->transform.position);
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