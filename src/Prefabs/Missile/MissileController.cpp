
#include <algorithm>
#include "Rtype/Game/Common/RtypeNetworkFactory.hpp"
#include "Prefabs/Missile/MissileController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/Animation.hpp"

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