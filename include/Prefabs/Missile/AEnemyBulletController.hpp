//
// Created by veyrie_f on 17/12/16.
//

#pragma once
#ifndef RTYPE_AENEMYBULLETCONTROLLER_HPP
#define RTYPE_AENEMYBULLETCONTROLLER_HPP

#include <string>
#include "Prefabs/RtypePrefab.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "Prefabs/Missile/ABulletController.hpp"

/**
 * @brief Base model for enemy's bullets
 */
class LIB_EXPORT AEnemyBulletController : public ABulletController
{
public:
    AEnemyBulletController(SaltyEngine::GameObject *go, std::string const& name = "AEnemyBulletController");
    virtual ~AEnemyBulletController();

public:
    /**
     * @brief Will emmit a sound and target a player by default
     */
    virtual void Start();
    /**
     * @brief Triggered on collision
     */
    void OnCollisionEnter(SaltyEngine::ICollider *);
};

#endif //RTYPE_AENEMYBULLETCONTROLLER_HPP
