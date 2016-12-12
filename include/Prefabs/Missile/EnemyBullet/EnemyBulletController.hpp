#pragma once

#ifndef RTYPE_EnemyBulletController_HPP
#define RTYPE_EnemyBulletController_HPP

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class EnemyBulletController : public SaltyEngine::SaltyBehaviour
{
public:
    EnemyBulletController(SaltyEngine::GameObject *go);
    virtual ~EnemyBulletController();

public:
    void Start();
    void Update();
    void OnCollisionEnter(SaltyEngine::ICollider *);

private:
    float m_vel = 100;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new EnemyBulletController(obj);
    }
};

#endif