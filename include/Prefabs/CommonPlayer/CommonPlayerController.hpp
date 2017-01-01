//
// Created by gaspar_q on 12/21/16.
//

#ifndef RTYPE_COMMONPLAYERCONTROLLER_HPP
#define RTYPE_COMMONPLAYERCONTROLLER_HPP

#include <Prefabs/RtypePrefab.hpp>
#include <Prefabs/GenericController.hpp>
#include <Prefabs/PodHandler/PodHandler.hpp>

class PREF_EXPORT CommonPlayerController : public RtypePrefab
{
private:
    static const float    timeoutDeath;
    static const float    timeoutInvicible;

public:
    enum Status
    {
        ALIVE,
        DEAD,
        INVINCIBLE
    };

public:
    CommonPlayerController(SaltyEngine::GameObject * const object, int lives);
    ~CommonPlayerController();

public:
    void Start();
    void FixedUpdate();
    Status GetStatus(void) const;

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj);

public:
    void Die();
    void Reborn();
    void BeamSoundActive(bool action);
//    void EnableBeam();

public:
    int GetGlobalLives() const;
    bool isAlive();
    bool isDead();
    void setInvincible();

    void OnCollisionEnter(SaltyEngine::ICollider *collider) override;

private:
    int global_lives;
    float timer;
    Status status;
    SaltyEngine::SFML::SpriteCollider2D    *collider2D;
    AGenericController  *controller;
    SaltyEngine::SFML::Animation *anim;
    SaltyEngine::SFML::SpriteRenderer *renderer;

public:
    SaltyEngine::GameObject		*m_beamSFX = nullptr;

private:
    SaltyEngine::Sound::ISound *beamSound = nullptr;

private:
    PodHandler *handler;
};

#endif //RTYPE_COMMONPLAYERCONTROLLER_HPP
