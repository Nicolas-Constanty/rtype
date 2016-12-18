#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML/Animation.hpp"
#include "Prefabs/GenericController.hpp"

class MonsterNeunoeilController : public AGenericController
{
public:
	MonsterNeunoeilController(SaltyEngine::GameObject *object);
	virtual ~MonsterNeunoeilController();

public:
	virtual void Die() const;
	virtual void TakeDamage(int amount);

public:
	void Start();
	void FixedUpdate();

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new MonsterNeunoeilController(obj);
	}

    void Move() override;

    void Shot() override;

private:
	float m_minShootInterval = 4;
	float m_maxShootInterval = 9;
	float m_currDelay = 0;
	bool m_isDead = false;
	float m_vel = 1;
	float m_walkDistance = 100;
    SaltyEngine::Vector m_startPoint;
    SaltyEngine::SFML::Animation *m_anim;
};

