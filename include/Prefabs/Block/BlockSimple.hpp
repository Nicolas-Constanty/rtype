#pragma once

#ifdef _WIN32
#ifdef BLOCKSIMPLE_EXPORTS
        #define BLOCKSIMPLE_API __declspec(dllexport)
    #else
        #define BLOCKSIMPLE_API __declspec(dllimport)
    #endif
#else
#define BLOCKSIMPLE_API
#endif

#ifndef BLOCKSIMPLE_HPP_
#define BLOCKSIMPLE_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C" {
class PREF_EXPORT BlockSimple : public SaltyEngine::GameObject {
public:
    BlockSimple();
    virtual ~BlockSimple();
};
PREF_EXPORT SaltyEngine::Object const *GetObjectPrefab();
}

#endif