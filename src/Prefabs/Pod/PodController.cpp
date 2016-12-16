//
// Created by gaspar_q on 12/16/16.
//

#include <SFML/Audio.hpp>
#include <SaltyEngine/Collider.hpp>
#include "Prefabs/Pod/PodController.hpp"

const std::vector<std::string>    PodController::lvlsprites = {
        "level1",
        "level2",
        "level3"
};

PodController::PodController(SaltyEngine::GameObject *const object) :
        RtypePrefab("PodController", object),
        attachedPlayer(NULL),
//        anim(NULL),
        level(0)
{

}

PodController::PodController(const std::string &name, SaltyEngine::GameObject *const object) :
        RtypePrefab(name, object),
        attachedPlayer(NULL),
//        anim(NULL),
        level(0)
{

}

SaltyEngine::Component *PodController::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new PodController(obj);
}

void PodController::OnStart()
{
//    anim = gameObject->GetComponent<SaltyEngine::AAnimationClip>();
//    if (!anim)
//        std::cerr << "[\e[31mError\e[0m]: No such animation clip component on PodController" << std::endl;
}

void PodController::OnTriggerEnter(SaltyEngine::ICollider *collider)
{
    if (attachedPlayer)
        return;

    if (isServerSide())
    {
        SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(collider);

        if (!c)
            return;

        if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::Player)
        {
            SaltyEngine::PlayerController   *player = c->gameObject->GetComponent<SaltyEngine::PlayerController>();

            if (!player)
                return;

            if (Attach(player))
            {
                try
                {
                    unsigned short podid = 0;

                    podid = getManager()->gameObjectContainer.GetServerObjectID(gameObject);
                    //                BroadCastReliable<TAKEPackageGame>(podid, player); todo uncomment when getPlayerID will be implemented
                }
                catch (std::runtime_error const &err)
                {
                    std::cerr << "Pod trigger enter: " << err.what() << " (while getting if of pod)" << std::endl;
                    throw err;
                }
            }
        }
    }
}

bool PodController::Upgrade()
{
    if (level < lvlsprites.size() - 1)
    {
        ++level;
//        if (anim)
//        {
            //todo set the animation clip at lvlsprites[level]
//        }
        return true;
    }
    return false;
}

bool PodController::Launch()
{
    if (attachedPlayer == NULL)
        return false;

    if (isServerSide())
    {
        unsigned short objid = 0;
        try
        {
            objid = getManager()->gameObjectContainer.GetServerObjectID(attachedPlayer->gameObject);
        }
        catch (std::runtime_error const &err)
        {
            std::cerr << "Pod launch: " << err.what() << " (while getting attached player)" << std::endl;
            throw err;
        }
        BroadCastReliable<LAUNCHPackageGame>(objid);
    }

    //todo add velocity to gameobject
    attachedPlayer = NULL;
    return true;
}

bool PodController::Call(SaltyEngine::Vector const &to)
{
    if (attachedPlayer != NULL)
        return false;

    if (isServerSide())
    {
        unsigned short podid = 0;

        try
        {
            podid = getManager()->gameObjectContainer.GetServerObjectID(gameObject);
        }
        catch (std::runtime_error const &err)
        {
            std::cerr << "Pod call: " << err.what() << " (while getting pod id)" << std::endl;
            throw err;
        }
        BroadCastReliable<CALLPackageGame>(podid, to.x, to.y);
    }
    //todo call to <to> position
    return true;
}

bool PodController::Attach(SaltyEngine::PlayerController *player)
{
    if (attachedPlayer != NULL)
        return false;
    //todo handle attachment of the pod
    //  -> check if a player already has a pod attached to him
    attachedPlayer = player;
    return true;
}
