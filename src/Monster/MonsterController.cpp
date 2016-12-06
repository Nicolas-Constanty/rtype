//#include "Monster/stdafx.h"
#include "Monster/MonsterController.hpp"

MonsterController::MonsterController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour(obj)
{
}


MonsterController::~MonsterController()
{
}

void MonsterController::Start()
{
}

void MonsterController::Update()
{
	this->gameObject->transform.Translate(SaltyEngine::Vector(0, -1));
}
