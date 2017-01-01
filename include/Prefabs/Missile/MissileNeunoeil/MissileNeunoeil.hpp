#ifndef MISSILENEUNOEIL_HPP_
#define MISSILENEUNOEIL_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
class PREF_EXPORT MissileNeunoeil : public SaltyEngine::GameObject
{
public:
    MissileNeunoeil();
    virtual ~MissileNeunoeil();
};

PREF_EXPORT SaltyEngine::Object const *GetObjectPrefab();
}

#endif