#include "SaltyEngine/SaltyEngine.hpp"
#include "Monster/MonsterController.hpp"

MonsterController::MonsterController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour(obj)
{
	m_currDelay = m_minShootInterval + ( ((m_maxShootInterval - m_minShootInterval) * rand()) / (RAND_MAX + 1) );
	//m_currDelay = m_minShootInterval + rand() % (m_maxShootInterval - m_minShootInterval);
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
		m_currDelay = m_minShootInterval + (((m_maxShootInterval - m_minShootInterval) * rand()) / (RAND_MAX + 1));
		SaltyEngine::GameObject *missile = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("MissileMedusa", this->gameObject->transform.position);
	}
	this->gameObject->transform.Translate(SaltyEngine::Vector(0, -1) * SaltyEngine::SaltyEngine::Instance().GetDeltaTime());
}

void MonsterController::Die() const
{
	// TODO : death
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