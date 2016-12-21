#ifdef _WIN32
#ifdef MISSILENEUNOEIL_EXPORTS
    #define MISSILENEUNOEIL_API __declspec(dllexport)
    #else
        #define MISSILENEUNOEIL_API __declspec(dllimport)
    #endif
#else
#define MISSILENEUNOEIL_API
#endif

#ifndef MISSILENEUNOEIL_HPP_
#define MISSILENEUNOEIL_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
class MissileNeunoeil : public SaltyEngine::GameObject
{
public:
    MissileNeunoeil();
    virtual ~MissileNeunoeil();
};

SaltyEngine::Object const *GetObjectPrefab();
}

#endif