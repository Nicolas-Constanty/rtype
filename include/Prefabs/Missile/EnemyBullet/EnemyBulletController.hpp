#pragma once

#ifndef RTYPE_EnemyBulletController_HPP
#define RTYPE_EnemyBulletController_HPP

#include "Rtype/Game/Server/GameServerObject.hpp"
#include "Prefabs/Missile/AEnemyBulletController.hpp"
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class PREF_EXPORT EnemyBulletController : public AEnemyBulletController
{
public:
    EnemyBulletController(SaltyEngine::GameObject *go);
    virtual ~EnemyBulletController();

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new EnemyBulletController(obj);
    }
};

#endif