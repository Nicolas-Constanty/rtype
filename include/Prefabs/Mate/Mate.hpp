//
// Created by gaspar_q on 12/12/16.
//

#ifdef _WIN32
#ifdef PLAYER_EXPORTS
#define PLAYER_API __declspec(dllexport)
#else
#define PLAYER_API __declspec(dllimport)
#endif
#else
#define PLAYER_API
#endif

#ifndef RTYPE_MATE_HPP
#define RTYPE_MATE_HPP

#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/GameObject.hpp"

#include <SaltyEngine/GameObject.hpp>

extern "C"
{
    class Mate : public SaltyEngine::GameObject
    {
    public:
        Mate();
        virtual ~Mate();
    };
    PLAYER_API SaltyEngine::Object const *GetObjectPrefab();
};

#endif //RTYPE_MATE_HPP
