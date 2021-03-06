//
// Created by gaspar_q on 12/26/16.
//

#include <Prefabs/Bonus/SpiralPodBonusController.hpp>
#include <Rtype/Game/Common/GameObjectID.hpp>
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>

const char SpiralPodBonusController::missile[12] = "LaserSpiral";

SpiralPodBonusController::SpiralPodBonusController(SaltyEngine::GameObject *object) :
        APodBonusController("SpiralPodBonusController", object)
{

}

SpiralPodBonusController::~SpiralPodBonusController()
{

}

SaltyEngine::Component *SpiralPodBonusController::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new SpiralPodBonusController(obj);
}

void SpiralPodBonusController::Start()
{
    ABonusController::Start();
    if (isServerSide())
    {
        unsigned short gameobjectId = GameObjectID::NewID();

        getManager()->gameObjectContainer.Add(gameobjectId, gameObject);
        BroadCastReliable<CREATEPackageGame>(gameObject->transform.GetPosition().x,
                                             gameObject->transform.GetPosition().y,
                                             RtypeNetworkFactory::GetIDFromName("SpiralBonus"),
                                             gameobjectId);
    }
}

std::string SpiralPodBonusController::getMissile() const
{
    return missile;
}

void SpiralPodBonusController::FixedUpdate() {
    gameObject->transform.Translate(-gameObject->transform.right() * m_vel);
}
