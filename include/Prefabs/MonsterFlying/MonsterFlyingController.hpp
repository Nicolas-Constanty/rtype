#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML/Animation.hpp"
#include "Prefabs/GenericController.hpp"

class MonsterFlyingController : public AGenericController
{
public:
	MonsterFlyingController(SaltyEngine::GameObject *object);
	virtual ~MonsterFlyingController();

public:
	virtual void Die() const;

public:
	void Start();
	void Update();

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new MonsterFlyingController(obj);
	}

    void Move() override;

    void Shot() override;

private:
	float m_minShootInterval = 4;
	float m_maxShootInterval = 9;
	float m_currDelay = 0;
	bool m_isDead = false;
	float m_vel = 10;
};

