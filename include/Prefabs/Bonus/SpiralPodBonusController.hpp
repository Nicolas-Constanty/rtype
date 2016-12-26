//
// Created by gaspar_q on 12/26/16.
//

#ifndef RTYPE_SPIRALPODBONUSCONTROLLER_HPP
#define RTYPE_SPIRALPODBONUSCONTROLLER_HPP

#include "APodBonusController.hpp"

class SpiralPodBonusController : public APodBonusController
{
private:
    static const char missile[12];

public:
    SpiralPodBonusController(SaltyEngine::GameObject *object);
    virtual ~SpiralPodBonusController();

public:
    virtual void Start();
    std::string getMissile() const;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj);
};

#endif //RTYPE_SPIRALPODBONUSCONTROLLER_HPP
