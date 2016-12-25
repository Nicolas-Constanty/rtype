#include "Rtype/Game/Common/RtypeNetworkFactory.hpp"
#include "Prefabs/Missile/AEnemyBulletController.hpp"
#include "Prefabs/Missile/MissileHoming/MissileHomingController.hpp"

MissileHomingController::MissileHomingController(SaltyEngine::GameObject *go) :
        ABulletController(go, "MissileHoming")
{
    m_vel = 4;
    m_fireSound = "fire";
    m_damage = 1;
    m_objectNameReplication = "MissileHoming";
}

MissileHomingController::~MissileHomingController()
{
}

void MissileHomingController::Start() {
    ABulletController::Start();
}

void MissileHomingController::OnCollisionEnter(SaltyEngine::ICollider *col) {
    SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(col);
    if (c)
    {
        if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::Enemy) {
            AGenericController *controller = c->gameObject->GetComponent<AGenericController>();
            if (controller)
                controller->TakeDamage(m_damage);
        }
    }
}
