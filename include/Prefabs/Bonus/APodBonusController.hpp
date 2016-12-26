//
// Created by gaspar_q on 12/26/16.
//

#ifndef RTYPE_PODBONUS_HPP
#define RTYPE_PODBONUS_HPP

#include "ABonusController.hpp"

class APodBonusController : public ABonusController
{
public:
    APodBonusController(std::string const &name, SaltyEngine::GameObject *object);
    virtual ~APodBonusController();

public:
    virtual void ExecuteBonus(SaltyEngine::GameObject *object);
};

#endif //RTYPE_PODBONUS_HPP
