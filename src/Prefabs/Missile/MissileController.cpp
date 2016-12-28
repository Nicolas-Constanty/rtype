#include "Prefabs/Missile/MissileController.hpp"

MissileController::MissileController(SaltyEngine::GameObject *go) : AEnemyBulletController(go, "MissileController")
{
    m_vel = 3;
    m_fireSound = "fire";
    m_damage = 1;
    m_objectNameReplication = "MissileMedusa";
}


MissileController::~MissileController()
{
}

void MissileController::Start()
{
    LoadManager();
    // Skip AEnemyBulletController to avoid auto-targeting
    ABulletController::Start();
}