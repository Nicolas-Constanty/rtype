//
// Created by veyrie_f on 29/12/16.
//

#ifndef RTYPE_LOGGERCONTROLLER_HPP
#define RTYPE_LOGGERCONTROLLER_HPP


#include "SaltyEngine/GameObject.hpp"

class LoggerController : public SaltyEngine::SaltyBehaviour
{
public:
    explicit LoggerController(SaltyEngine::GameObject *obj);

    virtual ~LoggerController();
    void Start() override;

    void OnMouseEnter() override;

    void OnMouseOver() override;

    void OnMouseExit() override;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject *const obj);
};

#endif //RTYPE_LOGGERCONTROLLER_HPP
