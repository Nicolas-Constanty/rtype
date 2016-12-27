//
// Created by gouet_v on 12/15/16.
//

#ifndef RTYPE_BEAM_HPP
#define RTYPE_BEAM_HPP

#ifdef _WIN32
#ifdef PLAYER_EXPORTS
#define PLAYER_API __declspec(dllexport)
#else
#define PLAYER_API __declspec(dllimport)
#endif
#else
#define PLAYER_API
#endif

#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Common/DLLexport.hpp"

extern "C"
{
class LIB_EXPORT Beam : public SaltyEngine::GameObject
{
public:
    Beam();
    virtual ~Beam();
};
LIB_EXPORT SaltyEngine::Object const *GetObjectPrefab();
};


#endif //RTYPE_BEAM_HPP
