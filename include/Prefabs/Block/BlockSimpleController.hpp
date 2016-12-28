//
// Created by wery_a on 18/12/16.
//

#ifndef BLOCKSIMPLE_CONTROLLER_HPP
#define BLOCKSIMPLE_CONTROLLER_HPP

#include "Prefabs/GenericController.hpp"

class  PREF_EXPORT BlockSimpleController: public RtypePrefab{
public:
    BlockSimpleController(SaltyEngine::GameObject * const gameObj);
    virtual ~BlockSimpleController();

public:
    void Start();
    void FixedUpdate();

private:
    float m_vel = 1;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new BlockSimpleController(obj);
    }
};

#endif //BLOCKSIMPLE_CONTROLLER_HPP
