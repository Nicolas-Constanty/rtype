//
// Created by gaspar_q on 12/26/16.
//

#ifndef RTYPE_SPIRALPODBONUSCONTROLLER_HPP
#define RTYPE_SPIRALPODBONUSCONTROLLER_HPP

#include "APodBonusController.hpp"

class PREF_EXPORT SpiralPodBonusController : public APodBonusController
{
private:
    static const char missile[12];

public:
    SpiralPodBonusController(SaltyEngine::GameObject *object);
    virtual ~SpiralPodBonusController();

public:
    virtual void Start();
    virtual void FixedUpdate();
    std::string getMissile() const;

private:
    float m_vel = 1;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj);
};

#endif //RTYPE_SPIRALPODBONUSCONTROLLER_HPP
