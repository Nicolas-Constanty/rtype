//
// Created by gaspar_q on 12/16/16.
//

#include <SFML/Audio.hpp>
#include <SaltyEngine/Collider.hpp>
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include <Rtype/Game/Common/GameObjectID.hpp>
#include "Prefabs/Pod/PodController.hpp"

const std::vector<std::string>    PodController::lvlsprites = {
        "Nacelle/Nacelle0",
        "Nacelle/Nacelle1",
        "Nacelle/Nacelle2"
};

PodController::PodController(SaltyEngine::GameObject *const object) :
        RtypePrefab("PodController", object),
        attachedPlayer(NULL),
        caller(NULL),
        shooter(NULL),
        isAtFront(true),
        anim(NULL),
        level(0),
        speed(0),
        sprr(NULL)
{

}

PodController::PodController(const std::string &name, SaltyEngine::GameObject *const object) :
        RtypePrefab(name, object),
        attachedPlayer(NULL),
        caller(NULL),
        shooter(NULL),
        isAtFront(true),
        anim(NULL),
        level(0),
        speed(0),
        sprr(NULL)
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
        BroadCastReliable<CREATEPackageGame>(gameObject->transform.GetPosition().x,
                                             gameObject->transform.GetPosition().y,
                                             RtypeNetworkFactory::GetIDFromName("Pod"),
                                             gameobjectId);
    }
    SaltyEngine::Vector2 winsize;
    SaltyEngine::Vector2 spritesize;

    if (!isServerSide())
    {
        SaltyEngine::SFML::Renderer *renderer = dynamic_cast<SaltyEngine::SFML::Renderer *>(SaltyEngine::Engine::Instance().GetRenderer());

        winsize = SaltyEngine::Vector2(renderer->GetRenderWindow()->getSize().x,
                                       renderer->GetRenderWindow()->getSize().y);
    }
    else
    {
        SaltyEngine::SFML::PhysicsHandler   *physicsHandler = dynamic_cast<SaltyEngine::SFML::PhysicsHandler *>(SaltyEngine::Engine::Instance().GetPhysicsHandler());

        winsize = SaltyEngine::Vector2(
                physicsHandler->GetSizeX(),
                physicsHandler->GetSizeY()
        );
    }

    sprr = gameObject->GetComponent<SaltyEngine::SFML::SpriteRenderer>();

    min = SaltyEngine::Vector2(
            sprr->GetSprite()->getTextureRect().width / 2,
            sprr->GetSprite()->getTextureRect().height / 2);
    max = SaltyEngine::Vector2(
            winsize.x / gameObject->transform.GetLocalScale().x - min.x,
            winsize.y / gameObject->transform.GetLocalScale().y - min.y);
    speed = 10;
    anim = gameObject->GetComponent<SaltyEngine::SFML::Animation>();
    getManager()->addPod(gameObject);
}

void PodController::FixedUpdate()
{
    if (speed > 0)
    {
        SaltyEngine::Vector2 newpos = gameObject->transform.GetPosition() + (SaltyEngine::Vector::left() * (isAtFront ? -1 : 1)) * speed;
        SaltyEngine::Vector2 const &pos = gameObject->transform.GetPosition();

        if ((newpos.x < max.x && newpos.y < max.y &&
            newpos.x > min.x && newpos.y > min.y) ||
            pos.x > max.x || pos.y > max.y ||
            pos.x < min.x || pos.y < min.y)
        {
            gameObject->transform.SetPosition(newpos);
        }
        else
        {
            speed = 0;
        }
    }
    else if (caller)
    {
        SaltyEngine::Vector2    direction = caller->gameObject->transform.GetPosition() - gameObject->transform.GetPosition();
        double l = 1.0 / sqrt(direction.x * direction.x + direction.y * direction.y);

        direction.x *= l;
        direction.y *= l;
        gameObject->transform.SetPosition(gameObject->transform.GetPosition() + direction);
    }
//    else if (!isAttached())
//    {
//        todo gravitate
//    }
}

void PodController::OnCollisionEnter(SaltyEngine::ICollider *collider)
{
    SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(collider);

    if (!c)
        return;
    if (isServerSide())
    {
        if (!attachedPlayer && c->gameObject->GetTag() == SaltyEngine::Layer::Tag::Player)
        {
            PodHandler   *player = c->gameObject->GetComponent<PodHandler>();

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
    if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::Enemy || c->gameObject->GetTag() == SaltyEngine::Layer::Tag::BulletEnemy)
    {
        SaltyEngine::Instantiate("ExplosionBasic", c->gameObject->transform.GetPosition());
        Destroy(c->gameObject);
    }
}

bool PodController::Upgrade()
{
    if (level < lvlsprites.size() - 1)
    {
        ++level;
        if (anim)
        {
            anim->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation(lvlsprites[level]), "Nacelle");
        }
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
        BroadCastReliable<LAUNCHPackageGame>(pod, player, gameObject->transform.GetPosition().x, gameObject->transform.GetPosition().y);
    }
    gameObject->transform.SetParent(NULL);
    shooter = attachedPlayer;
    attachedPlayer = NULL;
    speed = 10;
    return true;
}

bool PodController::Call(PodHandler *player)
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
        BroadCastReliable<CALLPackageGame>(podid, getManager()->gameObjectContainer.GetServerObjectID(player->gameObject));
    }
    caller = player;
    return true;
}

bool PodController::Attach(PodHandler *podController)
{
    return Attach(podController, gameObject->transform.GetPosition().x - podController->gameObject->transform.GetPosition().x > 0);
}

bool PodController::Attach(PodHandler *podController, bool front)
{
    std::cout << std::boolalpha << "att player: " << attachedPlayer << ", has pod: " << podController->HasPod() << std::endl;
    if (!attachedPlayer && !podController->HasPod())
    {
        speed = 0;
        if (shooter)
            shooter->UnlinkPod();
        shooter = NULL;
        caller = NULL;
        attachedPlayer = podController;
        gameObject->transform.SetParent(&attachedPlayer->gameObject->transform);
        if (front)
        {
            isAtFront = true;
            gameObject->transform.SetPosition(podController->gameObject->transform.GetPosition() + SaltyEngine::Vector(20, 0));
        }
        else
        {
            isAtFront = false;
            gameObject->transform.SetPosition(podController->gameObject->transform.GetPosition() - SaltyEngine::Vector(20, 0));
        }
        return attachedPlayer->Attach(this);
    }
    return false;
}

bool PodController::isAttached() const
{
    return attachedPlayer != NULL;
}

bool PodController::isAttachedTo(SaltyEngine::GameObject *object) const
{
    return isAttached() && attachedPlayer->gameObject == object;
}

PodHandler *PodController::getAttachedPlayer() const
{
    return attachedPlayer;
}
