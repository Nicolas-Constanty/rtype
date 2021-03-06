#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML/Animation.hpp"
#include "Prefabs/GenericController.hpp"

class PREF_EXPORT MonsterWalkerController : public AGenericController
{
public:
	MonsterWalkerController(SaltyEngine::GameObject *object);
	virtual ~MonsterWalkerController();

public:
	virtual void Die();
	virtual void TakeDamage(int amount);

public:
	void Start();
	void FixedUpdate();
//	void OnCollisionEnter(SaltyEngine::ICollider *col);

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new MonsterWalkerController(obj);
	}

	virtual int GetHighScore() const;

    void Move() override;

    void Shot() override;

private:
    void PlayAnim(std::string const& anim, bool queued = false) const;

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

