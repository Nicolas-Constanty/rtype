#include "Rtype/Game/Common/RtypeNetworkFactory.hpp"
#include "Prefabs/Missile/AEnemyBulletController.hpp"
#include "Prefabs/Missile/MissileHoming/MissileHomingController.hpp"

MissileHomingController::MissileHomingController(SaltyEngine::GameObject *go) :
        AEnemyBulletController(go, "MissileHoming")
{
    m_vel = 4;
    m_fireSound = "fire";
    m_damage = 1;
    m_objectNameReplication = "MissileHoming";
}

MissileHomingController::~MissileHomingController()
{
}

void MissileHomingController::Start() {
    LoadManager();

    if (!isServerSide())
    {
//        SaltyEngine::Sound::ISound *fire = SaltyEngine::SFML::AssetManager::Instance().GetSound(m_fireSound);
//        fire->Play();
    }

    if (isServerSide())
    {
        BroadCastReliable<CREATEPackageGame>(
                gameObject->transform.GetPosition().x,
                gameObject->transform.GetPosition().y,
                RtypeNetworkFactory::GetIDFromName(m_objectNameReplication),
                getManager()->gameObjectContainer.GetServerObjectID(gameObject),
                gameObject->transform.GetRotation());
    }
}
