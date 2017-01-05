#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Prefabs/GenericController.hpp"

class PREF_EXPORT MonsterController : public AGenericController
{
public:
	MonsterController(SaltyEngine::GameObject *object);
	virtual ~MonsterController();

public:
	virtual void Die();
	virtual void TakeDamage(int amount);

public:
	void Start();
	void FixedUpdate();
//	void OnCollisionEnter(SaltyEngine::ICollider *col);

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new MonsterController(obj);
	}

    void Move() override;

    void Shot() override;

	virtual int GetHighScore() const;

private:
	float m_minShootInterval = 1;
	float m_maxShootInterval = 4;
	float m_currDelay = 0;
	bool m_isDead = false;
	float m_vel = 50;
};

