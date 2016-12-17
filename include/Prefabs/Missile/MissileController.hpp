#pragma once

#ifndef RTYPE_MISSILECONTROLLER_HPP
#define RTYPE_MISSILECONTROLLER_HPP

#include <Rtype/Game/Server/GameServerObject.hpp>
#include <Prefabs/GenericController.hpp>
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class MissileController : public RtypePrefab//public SaltyEngine::SaltyBehaviour
{
public:
	MissileController(SaltyEngine::GameObject *go);
	virtual ~MissileController();

public:
	void Start();
	void FixedUpdate();

public:
	void SetTarget(SaltyEngine::GameObject const* target);

public:
	void Move();

private:
    float m_vel = 90;

public:
	virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
		return new MissileController(obj);
	}

//	Rtype::Game::Server::GameServerObject *gameServer;
//private:
};

#endif