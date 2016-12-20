//
// Created by wery_a on 18/12/16.
//

#ifndef {{PREFAB}}_CONTROLLER_HPP
#define {{PREFAB}}_CONTROLLER_HPP

#include "Prefabs/GenericController.hpp"

class {{Prefab}}Controller: public AGenericController {
public:
    {{Prefab}}Controller(SaltyEngine::GameObject * const gameObj);
    virtual ~{{Prefab}}Controller();

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
        return new {{Prefab}}Controller(obj);
    }
};

#endif //{{PREFAB}}_CONTROLLER_HPP
