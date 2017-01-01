//
// Created by gaspar_q on 12/26/16.
//

#ifndef RTYPE_ABONUS_HPP
#define RTYPE_ABONUS_HPP

#include <Prefabs/RtypePrefab.hpp>

class PREF_EXPORT ABonusController : public RtypePrefab
{
public:
    ABonusController(std::string const &name, SaltyEngine::GameObject *object);
    virtual ~ABonusController();

public:
    virtual void ExecuteBonus(SaltyEngine::GameObject *object) = 0;

public:
    virtual void Start();
    void OnCollisionEnter(SaltyEngine::ICollider *collider);
};

#endif //RTYPE_ABONUS_HPP
