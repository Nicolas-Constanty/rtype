#ifndef MISSILENEUNOEIL_HPP_
#define MISSILENEUNOEIL_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
class LIB_EXPORT MissileNeunoeil : public SaltyEngine::GameObject
{
public:
    MissileNeunoeil();
    virtual ~MissileNeunoeil();
};

LIB_EXPORT SaltyEngine::Object const *GetObjectPrefab();
}

#endif