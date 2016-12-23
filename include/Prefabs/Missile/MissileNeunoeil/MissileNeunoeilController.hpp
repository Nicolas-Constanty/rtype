//
// Created by wery_a on 18/12/16.
//

#ifndef MISSILENEUNOEIL_CONTROLLER_HPP
#define MISSILENEUNOEIL_CONTROLLER_HPP

#include <Prefabs/Missile/AEnemyBulletController.hpp>
#include "Prefabs/GenericController.hpp"

class MissileNeunoeilController: public AEnemyBulletController {
public:
    MissileNeunoeilController(SaltyEngine::GameObject *go);
    virtual ~MissileNeunoeilController();

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new MissileNeunoeilController(obj);
    }

    void Start() override;
};

#endif //MISSILENEUNOEIL_CONTROLLER_HPP
