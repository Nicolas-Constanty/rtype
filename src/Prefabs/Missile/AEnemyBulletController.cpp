//
// Created by veyrie_f on 17/12/16.
//

#include <Prefabs/GenericController.hpp>
#include "Rtype/Game/Common/RtypeNetworkFactory.hpp"
#include "SaltyEngine/SFML.hpp"
#include "Prefabs/Missile/AEnemyBulletController.hpp"

AEnemyBulletController::AEnemyBulletController(SaltyEngine::GameObject *go, std::string const &name) :
        RtypePrefab(name, go)
{
}

AEnemyBulletController::~AEnemyBulletController()
{
}

void AEnemyBulletController::Start()
{
    LoadManager();

    if (!isServerSide())
    {
        SaltyEngine::Sound::ISound *fire = SaltyEngine::SFML::AssetManager::Instance().GetSound(m_fireSound);
        fire->Play();
    }

    if (isServerSide())
    {
        std::list<SaltyEngine::GameObject*> players = SaltyEngine::GameObject::FindGameObjectsWithTag(SaltyEngine::Layer::Tag::Player);

        if (players.size() > 0)
        {
            this->SetTarget(*std::next(players.begin(), rand() % players.size()));
        }

        BroadCastReliable<CREATEPackageGame>(
                gameObject->transform.position.x,
                gameObject->transform.position.y,
                RtypeNetworkFactory::GetIDFromName(m_objectNameReplication),
                getManager()->gameObjectContainer.GetServerObjectID(gameObject),
                gameObject->transform.rotation);
    }
}

void AEnemyBulletController::FixedUpdate()
{
    gameObject->transform.Translate(gameObject->transform.right() * m_vel);
}

void AEnemyBulletController::OnCollisionEnter(SaltyEngine::ICollider *col)
{
    SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(col);
    if (c)
    {
        if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::Player) {
            AGenericController *controller = c->gameObject->GetComponent<AGenericController>();
            if (controller)
                controller->TakeDamage(m_damage);
        }
        if (c->gameObject != this->gameObject && c->gameObject->GetTag() != SaltyEngine::Layer::Tag::Enemy
                && c->gameObject->GetTag() != SaltyEngine::Layer::Tag::BulletEnemy) {
            // TODO : uncomment when objects are removed server side
//            SaltyEngine::Object::Destroy(this->gameObject);
        }
    }
}

void AEnemyBulletController::SetTarget(const SaltyEngine::GameObject *target)
{
    if (target != nullptr)
    {
        gameObject->transform.LookAt(target->transform);
    }
}
