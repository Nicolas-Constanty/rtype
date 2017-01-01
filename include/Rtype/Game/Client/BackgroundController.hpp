//
// Created by wery_a on 17/12/16.
//

#ifndef RTYPE_BACKGROUNDCONTROLLER_HPP
#define RTYPE_BACKGROUNDCONTROLLER_HPP

#include "SaltyEngine/SaltyBehaviour.hpp"
#include "SaltyEngine/GameObject.hpp"

class PREF_EXPORT BackgroundController : public SaltyEngine::SaltyBehaviour {
public:
    BackgroundController(SaltyEngine::GameObject * const gameObj);
    virtual ~BackgroundController();

public:
    void Start();
    void FixedUpdate();

private:
    SaltyEngine::GameObject *m_starfieldFar1;
    SaltyEngine::GameObject *m_starfieldFar2;
    SaltyEngine::GameObject *m_starfieldNear1;
    SaltyEngine::GameObject *m_starfieldNear2;
    SaltyEngine::GameObject *m_background;
    SaltyEngine::Vector2i   windowSize;
    float                   m_speed = 1;
    int                     m_start;
    int                     m_end;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj) {
        return new BackgroundController(obj);
    }
};

#endif //RTYPE_BACKGROUNDCONTROLLER_HPP
