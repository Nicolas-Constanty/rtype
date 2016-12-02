#include "ClientLauncher/Laser.hpp"

Laser::Laser(SaltyEngine::GameObject * const gamObj) : SaltyEngine::SaltyBehaviour(gamObj)
{
	m_speed = 20.0f;
}

void Laser::FixedUpdate()
{
	gameObject->transform.Translate(SaltyEngine::Vector(1, 0) * m_speed);
}

void Laser::OnCollisionEnter(SaltyEngine::ICollider *col)
{
	SaltyEngine::Debug::PrintSuccess("Laser hit something");
}

Laser::~Laser()
{
}
