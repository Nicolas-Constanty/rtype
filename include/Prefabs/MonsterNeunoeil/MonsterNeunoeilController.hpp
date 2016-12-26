#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML/Animation.hpp"
#include "Prefabs/GenericController.hpp"
#include "Common/CustomEnum.hpp"


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
	float m_minShootInterval = 1;
	float m_maxShootInterval = 2;
	float m_currDelay = 0;
	bool m_isDead = false;
	float m_vel = 1;
	float m_verticalDistance = 700;
	float m_horizontalDistance = 850;
    SaltyEngine::SFML::Animation *m_anim;
    float m_currTransitionDelay = 5;
    float m_transitionDelay = 5;

	bool m_isInvincible = false;
    SaltyEngine::GameObject *m_canons[4];
	SaltyEngine::SFML::SpriteRenderer *m_sprr;

private:
    enum EYE_STATE {E_STATIC, E_MOVING1, E_MOVING2, E_FIRST = E_STATIC, E_LAST = E_MOVING2};
    int m_dir = 1;
    Enum<EYE_STATE> m_state;

protected:
    void GoToNextState();
};

