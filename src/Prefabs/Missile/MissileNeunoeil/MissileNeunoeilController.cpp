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
    m_objectNameReplication = "EnemyBullet";
    // TODO remplacer la ligne du dessus => aller dans le code de gaspar_q
}

MissileNeunoeilController::~MissileNeunoeilController()
{
}