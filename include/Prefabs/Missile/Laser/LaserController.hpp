#pragma once

#ifndef RTYPE_LASERCONTROLLER_HPP
#define RTYPE_LASERCONTROLLER_HPP

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"
//#include "Prefabs/Player/PlayerController.hpp"
#include <map>
#include <Prefabs/Player/PlayerController.hpp>

class LaserController : public SaltyEngine::SaltyBehaviour
{
public:
    LaserController(SaltyEngine::GameObject *go);
    virtual ~LaserController();

public:
    void Start();
    void FixedUpdate();
    void OnCollisionEnter(SaltyEngine::ICollider *);
    void OnCollisionExit(SaltyEngine::ICollider *);

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
        return new LaserController(obj);
    }
};

#endif