#pragma once

#ifndef RTYPE_MISSILECONTROLLER_HPP
#define RTYPE_MISSILECONTROLLER_HPP

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class MissileController : public SaltyEngine::SaltyBehaviour
{
public:
	MissileController(SaltyEngine::GameObject *go);
	virtual ~MissileController();

public:
	void SetTarget(SaltyEngine::Vector v);
	void Update();

private:
	SaltyEngine::Vector m_targetPos;
    float m_vel = 10;

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new MissileController(obj);
	}
};

#endif