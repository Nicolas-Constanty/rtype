#include "Monster/stdafx.h"
#include "Monster/MonsterController.hpp"


MonsterController::MonsterController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour(obj)
{
}


MonsterController::~MonsterController()
{
}

void MonsterController::Start()
{
	std::cout << "STAAAART" << std::endl;
}

void MonsterController::Update()
{
	std::cout << "Update monster" << std::endl;
}
