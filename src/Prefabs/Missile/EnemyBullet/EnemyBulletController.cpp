#include "Prefabs/Missile/EnemyBullet/EnemyBulletController.hpp"

EnemyBulletController::EnemyBulletController(SaltyEngine::GameObject *go) :
        AEnemyBulletController(go, "EnemyBulletController")
{
    m_vel = 4;
    m_fireSound = "fire";
    m_damage = 1;
    m_objectNameReplication = "EnemyBullet";
}

EnemyBulletController::~EnemyBulletController()
{
}