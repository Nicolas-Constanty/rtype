//
// Created by wery_a on 18/12/16.
//

#ifndef {{CONTROLLER}}_CONTROLLER_HPP
#define {{CONTROLLER}}_CONTROLLER_HPP

#include "Prefabs/GenericController.hpp"

class {{Controller}}Controller: public SaltyEngine::SaltyBehaviour {
public:
    {{Controller}}Controller(SaltyEngine::GameObject * const gameObj);
    virtual ~{{Controller}}Controller();

public:
    void Start();
    void FixedUpdate();

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new {{Controller}}Controller(obj);
    }
};

#endif //{{CONTROLLER}}_CONTROLLER_HPP
