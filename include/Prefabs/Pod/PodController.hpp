//
// Created by gaspar_q on 12/16/16.
//

#ifndef RTYPE_PODCONTROLLER_HPP
#define RTYPE_PODCONTROLLER_HPP

#include <Prefabs/GenericController.hpp>
#include <Prefabs/Player/PlayerController.hpp>

class PodController : public RtypePrefab
{
private:
    static const std::vector<std::string>    lvlsprites;

public:
    explicit PodController(SaltyEngine::GameObject* const object);
    PodController(const std::string &name, SaltyEngine::GameObject * const object);

public:
    virtual SaltyEngine::Component *CloneComponent(SaltyEngine::GameObject* const obj);

public:
    virtual void Start();
    virtual void OnCollisionEnter(SaltyEngine::ICollider *);

public:
    bool Upgrade();
    bool Launch();
    bool Call(SaltyEngine::PlayerController *player);
    bool Attach(SaltyEngine::PlayerController *player);

public:
    bool isAttached() const;
    bool isAttachedTo(unsigned char playerID) const;
    SaltyEngine::PlayerController   *getAttachedPlayer() const;

private:
    SaltyEngine::PlayerController *attachedPlayer;
    SaltyEngine::PlayerController *caller;
    bool isAtFront;
//    SaltyEngine::AAnimationClip *anim;
    size_t level;
};


#endif //RTYPE_PODCONTROLLER_HPP
