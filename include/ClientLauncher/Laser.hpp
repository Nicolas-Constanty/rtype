#pragma once

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/Vector2.hpp"
#include "SaltyEngine/Debug.hpp"
#include "SaltyEngine/ICollider.hpp"

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

