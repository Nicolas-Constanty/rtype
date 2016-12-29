//
// Created by veyrie_f on 29/12/16.
//

#ifndef RTYPE_MANAGERPREFAB_HPP
#define RTYPE_MANAGERPREFAB_HPP

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
class LIB_EXPORT GameManagerPrefab : public SaltyEngine::GameObject
{
public:
    GameManagerPrefab();
    virtual ~GameManagerPrefab();
};

LIB_EXPORT SaltyEngine::Object const *GetObjectPrefab();
}

#endif //RTYPE_MANAGERPREFAB_HPP
