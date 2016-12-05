#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class MonsterController : public SaltyEngine::SaltyBehaviour
{
public:
	MonsterController(SaltyEngine::GameObject *object);
	virtual ~MonsterController();

public:
	void Start();
	void Update();

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new MonsterController(obj);
	}
};

