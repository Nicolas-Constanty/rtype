//
// Created by gaspar_q on 12/26/16.
//

#ifndef RTYPE_SPIRALPODBONUSCONTROLLER_HPP
#define RTYPE_SPIRALPODBONUSCONTROLLER_HPP

#include "APodBonusController.hpp"

class SpiralPodBonusController : public APodBonusController
{
public:
    SpiralPodBonusController(SaltyEngine::GameObject *object);
    virtual ~SpiralPodBonusController();

public:
    virtual void Start();
    //système pour différencier les missiles

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj);
};

#endif //RTYPE_SPIRALPODBONUSCONTROLLER_HPP
