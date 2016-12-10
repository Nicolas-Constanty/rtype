#pragma once

#ifndef RTYPE_LASERCONTROLLER_HPP
#define RTYPE_LASERCONTROLLER_HPP

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class LaserController : public SaltyEngine::SaltyBehaviour
{
public:
    LaserController(SaltyEngine::GameObject *go);
    virtual ~LaserController();

public:
    void Start();
    void Update();
    void OnCollisionEnter(SaltyEngine::ICollider *);

private:
    float m_vel = 100;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new LaserController(obj);
    }
};

#endif