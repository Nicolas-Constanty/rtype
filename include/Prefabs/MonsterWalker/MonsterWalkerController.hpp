#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/Animation.hpp"
#include "Prefabs/GenericController.hpp"
#include <Rtype/Game/Server/GameServerObject.hpp>

class MonsterWalkerController : public AGenericController
{
public:
	MonsterWalkerController(SaltyEngine::GameObject *object);
	virtual ~MonsterWalkerController();

public:
	virtual void Die() const;
	virtual void TakeDamage(int amount);

public:
	void Start();
	void Update();
//	void OnCollisionEnter(SaltyEngine::ICollider *col);

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new MonsterWalkerController(obj);
	}

private:
    void PlayAnim(std::string const& anim, bool queued = false) const;

private:
	float m_minShootInterval = 4;
	float m_maxShootInterval = 9;
	float m_currDelay = 0;
	bool m_isDead = false;
	float m_vel = 10;
	float m_walkDistance = 100;
    SaltyEngine::Vector m_startPoint;
    SaltyEngine::Animation<sf::Vector2i> *m_anim;
	Rtype::Game::Server::GameServerObject *gameServer;
};

