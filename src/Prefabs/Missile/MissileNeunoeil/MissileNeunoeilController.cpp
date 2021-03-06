#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include "Prefabs/Missile/AEnemyBulletController.hpp"
#include "Prefabs/Missile/MissileNeunoeil/MissileNeunoeilController.hpp"

MissileNeunoeilController::MissileNeunoeilController(SaltyEngine::GameObject *go) :
        AEnemyBulletController(go, "MissileNeunoeil")
{
    m_vel = 4;
    m_fireSound = "fire";
    m_damage = 1;
    m_objectNameReplication = "MissileNeunoeil";
}

MissileNeunoeilController::~MissileNeunoeilController()
{
}

void MissileNeunoeilController::Start() {
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
