#pragma once

#ifndef RTYPE_LASERCONTROLLER_HPP
#define RTYPE_LASERCONTROLLER_HPP

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include <map>

class LaserController : public SaltyEngine::SaltyBehaviour
{
public:
    static const std::map<int, std::string> damageSprite;

public:
    LaserController(SaltyEngine::GameObject *go);
    virtual ~LaserController();

public:
    void Start();
    void FixedUpdate();
    void OnCollisionEnter(SaltyEngine::ICollider *);

public:
    void Power(int damage);


private:
    float m_vel = 2; // 50
    int m_damage = 1;

private:
    SaltyEngine::Sound::ISound *soundFire;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new LaserController(obj);
    }
};

#endif