//
// Created by veyrie_f on 29/12/16.
//

#ifndef RTYPE_LOGGER_HPP
#define RTYPE_LOGGER_HPP

#include "SaltyEngine/GameObject.hpp"
#include "SaltyEngine/SFML.hpp"

extern "C"
{
class LIB_EXPORT Logger : public SaltyEngine::GameObject
{
public:
    Logger();
    virtual ~Logger();
};

LIB_EXPORT SaltyEngine::Object const *GetObjectPrefab();
}

#endif //RTYPE_LOGGER_HPP
