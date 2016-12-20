//
// Created by wery_a on 18/12/16.
//

#include "Prefabs/Missile/MissileNeunoeil/MissileNeunoeilController.hpp"

MissileNeunoeilController::MissileNeunoeilController(SaltyEngine::GameObject *go) :
        AEnemyBulletController(go, "MissileNeunoeilController")
{
    m_vel = 4;
    m_fireSound = "fire";
    m_damage = 1;
    m_objectNameReplication = "MissileNeunoeil";
}

MissileNeunoeilController::~MissileNeunoeilController()
{
}