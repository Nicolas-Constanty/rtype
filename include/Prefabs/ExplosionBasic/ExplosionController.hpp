#pragma once
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML/Animation.hpp"
#include "Prefabs/GenericController.hpp"

class ExplosionController : public SaltyEngine::SaltyBehaviour
{
public:
	ExplosionController(SaltyEngine::GameObject *object);
	virtual ~ExplosionController();

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new ExplosionController(obj);
	}
};