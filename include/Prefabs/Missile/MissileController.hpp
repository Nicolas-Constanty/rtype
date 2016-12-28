#pragma once

#ifndef RTYPE_MISSILECONTROLLER_HPP
#define RTYPE_MISSILECONTROLLER_HPP

#include "Rtype/Game/Server/GameServerObject.hpp"
#include "Prefabs/GenericController.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Prefabs/Missile/AEnemyBulletController.hpp"

class PREF_EXPORT MissileController : public AEnemyBulletController
{
public:
	MissileController(SaltyEngine::GameObject *go);
	virtual ~MissileController();

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new MissileController(obj);
	}
};

#endif