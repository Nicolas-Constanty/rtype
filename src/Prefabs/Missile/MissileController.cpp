#include "SaltyEngine/GameObject.hpp"
#include "Prefabs/Missile/MissileController.hpp"

MissileController::MissileController(SaltyEngine::GameObject *go) : SaltyEngine::SaltyBehaviour(go)
{
}


MissileController::~MissileController()
{
}

void MissileController::SetTarget(SaltyEngine::Vector v)
{
	m_targetPos = v;
}

void MissileController::Update()
{
//	this->gameObject->transform.Translate(this->gameObject->transform.up() * SaltyEngine::SaltyEngine::Instance().GetDeltaTime() * m_vel);
	gameObject->transform.Translate(SaltyEngine::Vector(1, 0) * m_vel);
}
