//
// Created by veyrie_f on 17/12/16.
//

#pragma once
#ifndef RTYPE_ABULLETCONTROLLER_HPP
#define RTYPE_ABULLETCONTROLLER_HPP

#include <string>
#include "Prefabs/RtypePrefab.hpp"
#include "SaltyEngine/SaltyEngine.hpp"

/**
 * @brief Base model for bullets
 */
class LIB_EXPORT ABulletController : public RtypePrefab
{
public:
    ABulletController(SaltyEngine::GameObject *go, std::string const& name = "ABulletController");
    virtual ~ABulletController();

public:
    /**
     * @brief Will emmit a sound and target a player by default
     */
    void Start();
    /**
     * @brief Will go right by default
     */
    void FixedUpdate();
    /**
     * @brief Sets the target for the bullet
     * @param target
     */
    virtual void SetTarget(SaltyEngine::GameObject const* target);

protected:
    float m_vel = 4;
    std::string m_fireSound = "fire";
    int m_damage = 1;
    std::string m_objectNameReplication = "Unknown";
    SaltyEngine::Sound::ISound *m_sound = nullptr;
};

#endif //RTYPE_ABULLETCONTROLLER_HPP
