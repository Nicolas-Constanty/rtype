#pragma once

#ifndef RTYPE_LASERSPIRALCONTROLLER_HPP
#define RTYPE_LASERSPIRALCONTROLLER_HPP

#include <map>
#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Prefabs/Player/PlayerController.hpp"

class LaserSpiralController : public SaltyEngine::SaltyBehaviour
{
public:
    LaserSpiralController(SaltyEngine::GameObject *go);
    virtual ~LaserSpiralController();

public:
    void Start();
    void FixedUpdate();
    void OnCollisionEnter(SaltyEngine::ICollider *);

    void AddPlayerController(SaltyEngine::PlayerController *playerController);

public:
    void Power(int damage);

private:
    float m_vel = 13; // 50
    int m_damage = 1;
    int m_targetNbr = 1;

private:
    SaltyEngine::Sound::ISound *soundFire;
    SaltyEngine::PlayerController *playerController;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new LaserSpiralController(obj);
    }
};

#endif