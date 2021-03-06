#ifdef _WIN32
#ifdef MISSILEHOMING_EXPORTS
        #define MISSILEHOMING_API __declspec(dllexport)
    #else
        #define MISSILEHOMING_API __declspec(dllimport)
    #endif
#else
#define MISSILEHOMING_API
#endif

#ifndef MISSILEHOMING_HPP_
#define MISSILEHOMING_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
class PREF_EXPORT MissileHoming : public SaltyEngine::GameObject
{
public:
    MissileHoming();
    virtual ~MissileHoming();
};

PREF_EXPORT SaltyEngine::Object const *GetObjectPrefab();
}

#endif