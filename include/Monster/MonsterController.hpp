#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "CommonPrefab/GenericController.hpp"

class MonsterController : public SaltyEngine::SaltyBehaviour, public AGenericController
{
public:
	MonsterController(SaltyEngine::GameObject *object);
	virtual ~MonsterController();

public:
	virtual void Die() const;
	virtual void TakeDamage(int amount);

public:
	void Start();
	void Update();

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new MonsterController(obj);
	}

private:
	float m_minShootInterval = 3;
	float m_maxShootInterval = 6;
	float m_currDelay = 0;
	bool m_isDead = false;
	float m_vel = 100;
};

