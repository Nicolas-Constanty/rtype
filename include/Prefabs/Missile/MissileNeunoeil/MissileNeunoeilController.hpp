//
// Created by wery_a on 18/12/16.
//

#ifndef MISSILENEUNOEIL_CONTROLLER_HPP
#define MISSILENEUNOEIL_CONTROLLER_HPP

#include "Prefabs/GenericController.hpp"

class MissileNeunoeilController: public AGenericController {
public:
    MissileNeunoeilController(SaltyEngine::GameObject * const gameObj);
    virtual ~MissileNeunoeilController();

public:
    virtual void Die();
    virtual void TakeDamage(int amount);

public:
    void Start();
    void FixedUpdate();
    void OnCollisionEnter(SaltyEngine::ICollider *col);

    void Move() override;

    void Shot() override;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new MissileNeunoeilController(obj);
    }
};

#endif //MISSILENEUNOEIL_CONTROLLER_HPP
