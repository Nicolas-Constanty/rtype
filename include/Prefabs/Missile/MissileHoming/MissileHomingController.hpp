//
// Created by veyrie_f on 18/12/16.
//

#ifndef MISSILEHOMING_CONTROLLER_HPP
#define MISSILEHOMING_CONTROLLER_HPP

#include "Prefabs/Missile/AEnemyBulletController.hpp"
#include "Prefabs/GenericController.hpp"

class MissileHomingController: public ABulletController {
public:
    MissileHomingController(SaltyEngine::GameObject *go);
    virtual ~MissileHomingController();

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new MissileHomingController(obj);
    }

    void Start() override;

    void OnCollisionEnter(SaltyEngine::ICollider *collider) override;

    void FixedUpdate() override;

private:
    SaltyEngine::GameObject *m_target = nullptr;
    float m_rotationVel = 100;
};

#endif //MISSILEHOMING_CONTROLLER_HPP
