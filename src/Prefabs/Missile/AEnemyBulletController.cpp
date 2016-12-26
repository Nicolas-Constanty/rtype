//
// Created by veyrie_f on 17/12/16.
//

#include "Prefabs/GenericController.hpp"
#include "Prefabs/Missile/AEnemyBulletController.hpp"

AEnemyBulletController::AEnemyBulletController(SaltyEngine::GameObject *go, std::string const &name) :
        ABulletController(go, name)
{
}

AEnemyBulletController::~AEnemyBulletController()
{
}

void AEnemyBulletController::Start()
{
    LoadManager();

    if (isServerSide())
    {
        std::vector<SaltyEngine::GameObject*> players = SaltyEngine::GameObject::FindGameObjectsWithTag(SaltyEngine::Layer::Tag::Player);

        if (players.size() > 0)
        {
            this->SetTarget(players[rand() % players.size()]);
        }
    }

    ABulletController::Start();
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