#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Prefabs/GenericController.hpp"

class MonsterController : public AGenericController
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
	void OnCollisionEnter(SaltyEngine::ICollider *col);

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new MonsterController(obj);
	}

private:
	float m_minShootInterval = 4;
	float m_maxShootInterval = 9;
	float m_currDelay = 0;
	bool m_isDead = false;
	float m_vel = 10;
};

