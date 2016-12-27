//
// Created by gaspar_q on 12/22/16.
//

#include <SaltyEngine/GameObject.hpp>
#include <Prefabs/PositionReplicator/PositionReplicator.hpp>

PositionReplicator::PositionReplicator(SaltyEngine::GameObject *object, float move_timeout) :
    RtypePrefab("PositionReplicator", object),
    m_timer(0),
    m_move_timout(move_timeout)
{

}

PositionReplicator::~PositionReplicator()
{

}

void PositionReplicator::Start()
{
    LoadManager();
}

void PositionReplicator::FixedUpdate()
{
    if (isServerSide())
    {
        m_timer -= SaltyEngine::Engine::Instance().GetFixedDeltaTime();
        if (m_timer <= 0)
        {
            m_timer = m_move_timout;
            BroadcastPackage<MOVEPackageGame>(
                    gameObject->transform.GetPosition().x,
                    gameObject->transform.GetPosition().y,
                    getManager()->gameObjectContainer.GetServerObjectID(gameObject));
        }
    }
}

SaltyEngine::Component *PositionReplicator::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new PositionReplicator(obj, m_move_timout);
}
