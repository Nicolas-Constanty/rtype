#pragma once

#include "SaltyEngine/GameObject.hpp"
#include "RtypePrefab.hpp"
#include <Rtype/Game/Server/GameServerObject.hpp>

class IGenericController
{
public:
	virtual ~IGenericController() {}

public:
	virtual void TakeDamage(int ammount) = 0;
	virtual int GetHealth() const = 0;
	virtual void Die() const = 0;
    virtual void Move() = 0;
    virtual void Shot() = 0;
};

class AGenericController : public RtypePrefab, public IGenericController
{
public:
    AGenericController(std::string const& name, SaltyEngine::GameObject *obj) : RtypePrefab(name, obj) {
//        gameServer = NULL;
    }
	~AGenericController() {}

public:
	virtual void TakeDamage(int amount)
	{
		m_health -= amount;
		if (m_health < 0)
		{
			m_health = 0;
		}
	}

	virtual int GetHealth() const
	{
		return m_health;
	}

public:
    virtual SaltyEngine::Component* CloneComponent(SaltyEngine::GameObject* const obj) = 0;

protected:
	int m_health = 0;
//	Rtype::Game::Server::GameServerObject *gameServer;
};