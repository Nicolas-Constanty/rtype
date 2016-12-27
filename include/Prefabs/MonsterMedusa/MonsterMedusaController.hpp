#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML/Animation.hpp"
#include "Prefabs/GenericController.hpp"
#include "Common/CustomEnum.hpp"


class LIB_EXPORT MonsterMedusaController : public AGenericController
{
public:
	MonsterMedusaController(SaltyEngine::GameObject *object);
	virtual ~MonsterMedusaController();

public:
	virtual void Die();
	virtual void TakeDamage(int amount);

public:
	void Start();
	void FixedUpdate();

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new MonsterMedusaController(obj);
	}

    void Move() override;

    void Shot() override;

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
    int m_dir = 1;

	SaltyEngine::SFML::SpriteRenderer *m_sprr;

private:
    enum MEDUSA_STATE {E_MOVING, E_SPAWNING, E_FIRST = E_MOVING, E_LAST = E_SPAWNING};
    Enum<MEDUSA_STATE> m_state;

protected:
    void GoToNextState();
};

