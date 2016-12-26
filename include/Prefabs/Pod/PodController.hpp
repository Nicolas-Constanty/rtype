//
// Created by gaspar_q on 12/16/16.
//

#ifndef RTYPE_PODCONTROLLER_HPP
#define RTYPE_PODCONTROLLER_HPP

#include <Prefabs/GenericController.hpp>
#include <Prefabs/Player/PlayerController.hpp>
#include <Prefabs/PodHandler/PodHandler.hpp>

class PodController : public RtypePrefab
{
public:
    explicit PodController(SaltyEngine::GameObject* const object);
    PodController(const std::string &name, SaltyEngine::GameObject * const object);

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj);

public:
    virtual void Start();
    virtual void FixedUpdate();
    virtual void OnCollisionEnter(SaltyEngine::ICollider *);

public:
    bool Upgrade(std::string const &rocket);
    bool Launch();
    bool Call(PodHandler *podController);
    bool Attach(PodHandler *podController);
    bool Attach(PodHandler *podController, bool front);

public:
    bool isAttached() const;
    bool isAttachedTo(SaltyEngine::GameObject *obj) const;
    PodHandler   *getAttachedPlayer() const;

public:
    bool Shot();

private:
    PodHandler *attachedPlayer;
    PodHandler *caller;
    PodHandler *shooter;
    bool isAtFront;
    SaltyEngine::SFML::Animation *anim;
    size_t level;
    double speed;
    SaltyEngine::SFML::SpriteRenderer   *sprr;
    SaltyEngine::Vector2    min;
    SaltyEngine::Vector2    max;
    std::string missile;
};


#endif //RTYPE_PODCONTROLLER_HPP
