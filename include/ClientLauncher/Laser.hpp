#pragma once

#include "SaltyEngine/SaltyBehaviour.hpp"

class Laser : public SaltyEngine::SaltyBehaviour
{
public:
	explicit Laser(SaltyEngine::GameObject* const gamObj);
	void FixedUpdate() override;
	void OnCollisionEnter(SaltyEngine::ICollider *) override;
	~Laser();

private:
	float m_speed;
};

