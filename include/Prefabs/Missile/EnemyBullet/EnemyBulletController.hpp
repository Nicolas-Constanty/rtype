#pragma once

#ifndef RTYPE_EnemyBulletController_HPP
#define RTYPE_EnemyBulletController_HPP

#include <Rtype/Game/Server/GameServerObject.hpp>
#include <Prefabs/RtypePrefab.hpp>
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class EnemyBulletController : public RtypePrefab
{
public:
    EnemyBulletController(SaltyEngine::GameObject *go);
    virtual ~EnemyBulletController();

public:
    void Start();
    void FixedUpdate();
    void OnCollisionEnter(SaltyEngine::ICollider *);

private:
    float m_vel = 4;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new EnemyBulletController(obj);
    }

//private:
//    Rtype::Game::Server::GameServerObject *gameServer;
};

#endif