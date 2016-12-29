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
};


#endif //RTYPE_LOGGERCONTROLLER_HPP
