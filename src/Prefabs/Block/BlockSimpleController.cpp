//
// Created by wery_a on 18/12/16.
//

#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include "Prefabs/Block/BlockSimpleController.hpp"

BlockSimpleController::BlockSimpleController(SaltyEngine::GameObject * const gameObj) : RtypePrefab("BlockSimpleController", gameObj) {
//    : SaltyBehaviour("BlockSimpleController", gameObj) {

}

BlockSimpleController::~BlockSimpleController() {
}

void BlockSimpleController::Start() {
    LoadManager();
    if (isServerSide()) {
        BroadCastReliable<CREATEPackageGame>(
                gameObject->transform.GetPosition().x,
                gameObject->transform.GetPosition().y,
                RtypeNetworkFactory::GetIDFromName("BlockSimple"),
                getManager()->gameObjectContainer.GetServerObjectID(gameObject),
                gameObject->transform.GetRotation());
    }
}

void BlockSimpleController::FixedUpdate() {
    gameObject->transform.Translate(-gameObject->transform.right() * m_vel);
}