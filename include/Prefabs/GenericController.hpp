#pragma once

#include "SaltyEngine/GameObject.hpp"

class IGenericController
{
public:
	virtual ~IGenericController() {}

public:
	virtual void TakeDamage(int ammount) = 0;
	virtual int GetHealth() const = 0;
	virtual void Die() const = 0;
};

class AGenericController : public SaltyEngine::SaltyBehaviour, public IGenericController
{
public:
    AGenericController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour("AGenericController", obj) {}
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
    virtual Component* CloneComponent(SaltyEngine::GameObject* const obj) = 0;

protected:
	int m_health = 0;
};