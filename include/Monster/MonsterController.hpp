#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class MonsterController : public SaltyEngine::SaltyBehaviour
{
public:
	MonsterController(SaltyEngine::GameObject *object);
	virtual ~MonsterController();

public:
	void Update() {
		std::cout << "Update" << std::endl;
	}
};

