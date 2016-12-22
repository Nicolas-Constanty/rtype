//
// Created by gaspar_q on 12/22/16.
//

#ifndef RTYPE_POSITIONREPLICATOR_HPP
#define RTYPE_POSITIONREPLICATOR_HPP

#include "../RtypePrefab.hpp"
#include "../../SaltyEngine/GameObject.hpp"

class PositionReplicator : public RtypePrefab
{
public:
    PositionReplicator(SaltyEngine::GameObject *object, float move_timeout = 1);
    ~PositionReplicator();

public:
    void Start();
    void FixedUpdate();

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj);

private:
    float m_timer;
    const float m_move_timout;
};

#endif //RTYPE_POSITIONREPLICATOR_HPP
