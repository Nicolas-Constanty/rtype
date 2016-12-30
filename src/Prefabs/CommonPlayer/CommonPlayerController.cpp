//
// Created by gaspar_q on 12/21/16.
//

#include <Prefabs/CommonPlayer/CommonPlayerController.hpp>

const float    CommonPlayerController::timeoutDeath  = 3;
const float    CommonPlayerController::timeoutInvicible = 3;

CommonPlayerController::CommonPlayerController(SaltyEngine::GameObject * const object, int lives) :
    RtypePrefab("CommonPlayerController", object),
    global_lives(lives),
    timer(0),
    status(ALIVE),
    collider2D(nullptr),
    controller(nullptr),
    anim(nullptr),
    renderer(nullptr)
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
    renderer = gameObject->GetComponent<SaltyEngine::SFML::SpriteRenderer>();
    anim = gameObject->AddComponent<SaltyEngine::SFML::Animation>(false, SaltyEngine::AnimationConstants::WrapMode::LOOP);
    std::string sprr = renderer->GetSprite()->GetName();

    SaltyEngine::SFML::AnimationClip *clip = new SaltyEngine::SFML::AnimationClip("Invincibility", 4, SaltyEngine::AnimationConstants::WrapMode::LOOP);
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite(sprr));
    clip->AddSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite(sprr));
    clip->AddEvent([this](){ renderer->SetColor(SaltyEngine::Color(1, 1, 1, 0)); }, 0);
    clip->AddEvent([this](){ renderer->SetColor(SaltyEngine::Color(1, 1, 1, 1)); }, 1);
    anim->AddClip(clip, "Invincibility");
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
            if (timer <= 0)
            {
                status = ALIVE;
                if (controller)
                    controller->SetHealth(1);
                anim->Stop("Invincibility");
                renderer->SetColor(SaltyEngine::Color(1, 1, 1));
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
    --global_lives;
    if (isServerSide())
    {
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
    anim->Play("Invincibility");
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

void CommonPlayerController::OnCollisionEnter(SaltyEngine::ICollider *collider) {
    SaltyEngine::SFML::SpriteCollider2D *col = dynamic_cast<SaltyEngine::SFML::SpriteCollider2D*>(collider);
    if (col)
    {
        if (isServerSide() && isAlive()) {
            if (!col->gameObject->CompareTag(SaltyEngine::Layer::Tag::BulletPlayer)
                && !col->gameObject->CompareTag(SaltyEngine::Layer::Tag::Player)
                   && !col->gameObject->CompareTag(SaltyEngine::Layer::Tag::Bonus)) {
                Die();
            }
        }
    }
}

CommonPlayerController::Status CommonPlayerController::GetStatus(void) const {
    return status;
}

int CommonPlayerController::GetGlobalLives() const {
    return global_lives;
}
