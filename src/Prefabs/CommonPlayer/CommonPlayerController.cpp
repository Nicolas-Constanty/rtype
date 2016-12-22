//
// Created by gaspar_q on 12/21/16.
//

#include <Prefabs/CommonPlayer/CommonPlayerController.hpp>

const float    CommonPlayerController::timeoutDeath  = 3;
const float    CommonPlayerController::timeoutInvicible = 3;

CommonPlayerController::CommonPlayerController(SaltyEngine::GameObject * const object, int lives) :
    RtypePrefab("CommonPlayerController", object),
    global_lives(lives),
    status(ALIVE),
    collider2D(nullptr)
{

}

CommonPlayerController::~CommonPlayerController()
{

}

void CommonPlayerController::Start()
{
    LoadManager();
    collider2D = gameObject->GetComponent<SaltyEngine::SFML::SpriteCollider2D>();
    controller = gameObject->GetComponent<AGenericController>();
}

void CommonPlayerController::FixedUpdate()
{
    timer -= SaltyEngine::Engine::Instance().GetFixedDeltaTime();
    switch (status)
    {
        case ALIVE:
            break;
        case DEAD:
            if (isServerSide() && timer <= 0)
            {
                BroadCastReliable<REBORNPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
                Reborn();
            }
            break;
        case INVINCIBLE:
            if (isServerSide() && timer <= 0)
            {
                status = ALIVE;
                if (controller)
                    controller->SetHealth(1);
            }
            break;
        default:
            break;
    }
}

void CommonPlayerController::Die()
{
    if (isServerSide() && !isAlive())
        return;
    gameObject->SetActive(false);
    status = DEAD;
    if (isServerSide())
    {
        --global_lives;
        timer = timeoutDeath;
        BroadCastReliable<DEATHPackage>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
    }
    else
    {
        SaltyEngine::Instantiate("ExplosionBasic", gameObject->transform.GetPosition());
    }
    if (global_lives == -1)
    {
        if (isServerSide())
        {
            BroadCastReliable<DIEPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
            Destroy(gameObject);
        }
    }
}

bool CommonPlayerController::isAlive()
{
    return status == ALIVE;
}

void CommonPlayerController::Reborn()
{
    status = INVINCIBLE;
    timer = timeoutInvicible;
    gameObject->SetActive(true);
}

SaltyEngine::Component *CommonPlayerController::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new CommonPlayerController(obj, global_lives);
}

bool CommonPlayerController::isDead()
{
    return status == DEAD;
}

void CommonPlayerController::setInvincible()
{
    status = INVINCIBLE;
}
