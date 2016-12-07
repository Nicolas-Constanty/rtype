#pragma once
#include "SaltyEngine/SaltyEngine.hpp"

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
};