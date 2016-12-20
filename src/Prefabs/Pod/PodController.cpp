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
//    anim = gameObject->GetComponent<SaltyEngine::AAnimationClip>();
//    if (!anim)
//        std::cerr << "[\e[31mError\e[0m]: No such animation clip component on PodController" << std::endl;
}

void PodController::OnCollisionEnter(SaltyEngine::ICollider *collider)
{
    std::cout << "\e[32mPod is colliding\e[0m" << std::endl;
    if (attachedPlayer)
        return;
    std::cout << "Not attached" << std::endl;
    if (isServerSide())
    {
        std::cout << "Server side" << std::endl;
        SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(collider);

        if (!c)
            return;

        std::cout << "Collider cast" << std::endl;
        if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::Player)
        {
            SaltyEngine::PlayerController   *player = c->gameObject->GetComponent<SaltyEngine::PlayerController>();

            std::cout << "Found player" << std::endl;
            if (!player)
                return;

            if (Attach(player))
            {
                std::cout << "Attached" << std::endl;
                try
                {
                    unsigned short podid = 0;

                    podid = getManager()->gameObjectContainer.GetServerObjectID(gameObject);
                    std::cout << "Broadcasting take package: " << podid << ", " << player->GetPlayerID() << std::endl;
                    BroadCastReliable<TAKEPackageGame>(podid, getManager()->gameObjectContainer.GetServerObjectID(player->gameObject));
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
    if (isAtFront)
    {
        //todo set the position juste before the ship
    }
    else
    {
        //todo set the position juste after the ship
    }
    //todo add velocity to gameobject
    gameObject->transform.SetParent(NULL);
    attachedPlayer = NULL;
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
            throw err;
        }
        BroadCastReliable<CALLPackageGame>(podid, getManager()->GetPlayerID(player->gameObject));
    }
    caller = player;
    return true;
}

bool PodController::Attach(SaltyEngine::PlayerController *player)
{
    if (!attachedPlayer && !player->HasPod())
    {
        //todo handle attachment of the pod
        attachedPlayer = player;
        gameObject->transform.SetParent(&attachedPlayer->gameObject->transform);
        if (player->gameObject->transform.position.x - player->gameObject->transform.position.x > 0)
        {
            std::cout << "Attach pod at front" << std::endl;
            //todo set the position of the pod
            isAtFront = true;
        }
        else
        {
            std::cout << "Attach pod at the back" << std::endl;
            //todo set the position of the pod
            isAtFront = false;
        }
        return attachedPlayer->Attach(this);
    }
    std::cout << "attachedPlayer: " << attachedPlayer << ", hasPod: " << std::boolalpha << player->HasPod() << std::endl;
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
