#include <SaltyEngine/Maths.hpp>
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

    if (!isServerSide())
    {
        std::vector<SaltyEngine::GameObject*> enemies = SaltyEngine::GameObject::FindGameObjectsWithTag(SaltyEngine::Layer::Tag::Enemy);

        if (enemies.size() > 0)
        {
            m_target = enemies[rand() % enemies.size()];
        }
    }
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

void MissileHomingController::FixedUpdate() {
    static int packet_count = 0;

    if (m_target != nullptr && m_target->transform.GetPosition().x - this->gameObject->transform.GetPosition().x <= 90)
    {
        float currRot = this->gameObject->transform.GetRotation();
        float targetRot = SaltyEngine::Vector2::Angle(this->gameObject->transform.GetPosition(),
                                                      m_target->transform.GetPosition());
        float lerpRot = SaltyEngine::Mathf::LerpAngle(currRot, targetRot,
                                                      SaltyEngine::Engine::Instance().GetFixedDeltaTime() * 6);

//        std::cout << "Current rotation = " << currRot << std::endl;
//        std::cout << "Target rotation = " << targetRot << std::endl;
//        std::cout << "Once lerped = " << lerpRot << std::endl;

        this->gameObject->transform.SetRotation(lerpRot);
    }
    if (isServerSide() && packet_count % 60 == 0)
    {
        SendPackage<MOVEPackageGame>(gameObject->transform.GetPosition().x,
                                     gameObject->transform.GetPosition().y,
                                     getManager()->gameObjectContainer.GetServerObjectID(gameObject));
    }
    ++packet_count;
    gameObject->transform.Translate(gameObject->transform.right() * m_vel);
}
