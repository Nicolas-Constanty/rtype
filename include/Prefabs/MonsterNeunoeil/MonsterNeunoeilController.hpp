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
	virtual void Die();
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

	void SetInvincibility(bool invincible);

	void OnCollisionEnter(SaltyEngine::ICollider *collider) override;

private:
	float m_minShootInterval = 2;
	float m_maxShootInterval = 3;
	float m_currDelay = 0;
	bool m_isDead = false;
	float m_vel = 1;
	float m_verticalDistance = 100;
	float m_horizontalDistance = 850;
    SaltyEngine::Vector m_startPoint;
    SaltyEngine::SFML::Animation *m_anim;

	bool m_isInvincible = false;
    SaltyEngine::GameObject *m_canons[4];

private:
    enum EYE_STATES {E_STATIC, E_MOVING};
    int m_dir = 1;
    EYE_STATES m_eyeState = E_MOVING;
};

