//
// Created by veyrie_f on 17/12/16.
//

#pragma once
#ifndef RTYPE_AENEMYBULLETCONTROLLER_HPP
#define RTYPE_AENEMYBULLETCONTROLLER_HPP

#include <string>
#include "Prefabs/RtypePrefab.hpp"
#include "SaltyEngine/SaltyEngine.hpp"

/**
 * @brief Base model for enemy's bullets
 */
class AEnemyBulletController : public RtypePrefab
{
public:
    AEnemyBulletController(SaltyEngine::GameObject *go, std::string const& name = "AEnemyBulletController");
    virtual ~AEnemyBulletController();

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
     * @brief Triggered on collision
     */
    void OnCollisionEnter(SaltyEngine::ICollider *);
    /**
     * @brief Sets the target for the bullet
     * @param target
     */
    virtual void SetTarget(SaltyEngine::GameObject const* target);

protected:
    float m_vel = 4;
    std::string m_fireSound = "fire";
    int m_damage = 1;
    std::string m_objectNameReplication;
};

#endif //RTYPE_AENEMYBULLETCONTROLLER_HPP
