//
// Created by gaspar_q on 12/16/16.
//

#include <SFML/Audio.hpp>
#include <SaltyEngine/Collider.hpp>
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include <Rtype/Game/Common/GameObjectID.hpp>
#include "Prefabs/Pod/PodController.hpp"

const std::vector<std::string>    PodController::lvlsprites = {
        "level1",
        "level2",
        "level3"
};

PodController::PodController(SaltyEngine::GameObject *const object) :
        RtypePrefab("PodController", object),
        attachedPlayer(NULL),
        caller(NULL),
        isAtFront(false),
//        anim(NULL),
        level(0)
{

}

PodController::PodController(const std::string &name, SaltyEngine::GameObject *const object) :
        RtypePrefab(name, object),
        attachedPlayer(NULL),
        caller(NULL),
        isAtFront(false),
//        anim(NULL),
        level(0)
{

}

SaltyEngine::Component *PodController::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new PodController(obj);
}

void PodController::Start()
{
    LoadManager();
    if (isServerSide())
    {
        unsigned short gameobjectId = GameObjectID::NewID();

        getManager()->gameObjectContainer.Add(gameobjectId, gameObject);
        BroadCastReliable<CREATEPackageGame>(gameObject->transform.position.x,
                                             gameObject->transform.position.y,
                                             RtypeNetworkFactory::GetIDFromName("Pod"),
                                             gameobjectId);
    }
    speed = 10;
//    anim = gameObject->GetComponent<SaltyEngine::AAnimationClip>();
//    if (!anim)
//        std::cerr << "[\e[31mError\e[0m]: No such animation clip component on PodController" << std::endl;
}

void PodController::FixedUpdate()
{
    if (speed > 0)
    {
        gameObject->transform.SetPosition(gameObject->transform.position + (SaltyEngine::Vector::left() * (isAtFront ? -1 : 1)) * speed);
    }
//    else if (!isAttached())
//    {
//        todo gravitate
//    }
}

void PodController::OnCollisionEnter(SaltyEngine::ICollider *collider)
{
    if (attachedPlayer)
        return;

    speed = 0;
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
                    BroadCastReliable<TAKEPackageGame>(podid, getManager()->gameObjectContainer.GetServerObjectID(player->gameObject), isAtFront);
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
        unsigned short player = 0;
        unsigned short pod = 0;

        try
        {
            player = getManager()->gameObjectContainer.GetServerObjectID(attachedPlayer->gameObject);
            pod = getManager()->gameObjectContainer.GetServerObjectID(gameObject);
        }
        catch (std::runtime_error const &err)
        {
            std::cerr << "Pod launch: " << err.what() << " (while getting attached player)" << std::endl;
            return false;
        }
        BroadCastReliable<LAUNCHPackageGame>(pod, player);
    }
//    if (isAtFront)
//    {
//        //todo set the position juste before the ship
//    }
//    else
//    {
//        //todo set the position juste after the ship
//    }
    //todo add velocity to gameobject
    std::cout << "Launching pod" << std::endl;
    gameObject->transform.SetParent(NULL);
    attachedPlayer = NULL;
    speed = 10;
    return true;
}

bool PodController::Call(SaltyEngine::PlayerController *player)
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
            return false;
        }
        BroadCastReliable<CALLPackageGame>(podid, getManager()->GetPlayerID(player->gameObject));
    }
    caller = player;
    return true;
}

bool PodController::Attach(SaltyEngine::PlayerController *player)
{
    return Attach(player, gameObject->transform.position.x - player->gameObject->transform.position.x > 0);
}

bool PodController::Attach(SaltyEngine::PlayerController *player, bool front)
{
    if (!attachedPlayer && !player->HasPod())
    {
        attachedPlayer = player;
        gameObject->transform.SetParent(&attachedPlayer->gameObject->transform);
        if (front)
        {
            isAtFront = true;
            gameObject->transform.SetPosition(player->gameObject->transform.position + SaltyEngine::Vector(20, 0));
        }
        else
        {
            isAtFront = false;
            gameObject->transform.SetPosition(player->gameObject->transform.position - SaltyEngine::Vector(20, 0));
        }
        return attachedPlayer->Attach(this);
    }
    return false;
}

bool PodController::isAttached() const
{
    return attachedPlayer != NULL;
}

bool PodController::isAttachedTo(unsigned char playerID) const
{
    return isAttached() && attachedPlayer->GetPlayerID() == playerID;
}

SaltyEngine::PlayerController *PodController::getAttachedPlayer() const
{
    return attachedPlayer;
}
