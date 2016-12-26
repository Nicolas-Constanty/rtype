//
// Created by veyrie_f on 17/12/16.
//

#include "Prefabs/GenericController.hpp"
#include "Rtype/Game/Common/RtypeNetworkFactory.hpp"
#include "Prefabs/Missile/ABulletController.hpp"

ABulletController::ABulletController(SaltyEngine::GameObject *go, std::string const &name) :
        RtypePrefab(name, go)
{
}

ABulletController::~ABulletController()
{
    if (m_sound != nullptr)
        delete m_sound;
}

void ABulletController::Start()
{
    LoadManager();
    if (!isServerSide())
    {
        m_sound = SaltyEngine::SFML::AssetManager::Instance().GetSound(m_fireSound);
        m_sound->Play();
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

void ABulletController::FixedUpdate()
{
    gameObject->transform.Translate(gameObject->transform.right() * m_vel);
}

void ABulletController::SetTarget(const SaltyEngine::GameObject *target)
{
    if (target != nullptr)
    {
        gameObject->transform.LookAt(target->transform);
    }
}
