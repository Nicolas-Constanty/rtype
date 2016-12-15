//
// Created by gouet_v on 12/15/16.
//

#ifndef RTYPE_BEAMCONTROLLER_HPP
#define RTYPE_BEAMCONTROLLER_HPP

#include <SaltyEngine/SaltyBehaviour.hpp>

class BeamController : public SaltyEngine::SaltyBehaviour
{
public:
    BeamController(SaltyEngine::GameObject *const object);
    virtual ~BeamController();

public:
    void Start();

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new BeamController(obj);
    }
};


#endif //RTYPE_BEAMCONTROLLER_HPP
