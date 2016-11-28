#include "Monster/MonsterController.hpp"


MonsterController::MonsterController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour(obj)
{
}


MonsterController::~MonsterController()
{
}

void MonsterController::FixedUpdate()
{
	gameObject->transform.Translate(SaltyEngine::Vector(1, 0));
}
