#include <Rtype/Game/Common/GameObjectID.hpp>
#include <SaltyEngine/Maths.hpp>
#include "Rtype/Game/Common/RtypeNetworkFactory.hpp"
#include "Prefabs/Missile/MissileController.hpp"
#include "Prefabs/MonsterFlying/MonsterFlyingController.hpp"
#include "SaltyEngine/SFML.hpp"

MonsterFlyingController::MonsterFlyingController(SaltyEngine::GameObject *obj) : AGenericController("MonsterFlyingController", obj)
{
    m_health = 1;
}


MonsterFlyingController::~MonsterFlyingController()
{
}

void MonsterFlyingController::Start()
{
    LoadManager();
	m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
    if (isServerSide()) {
        BroadCastReliable<CREATEPackageGame>(gameObject->transform.GetPosition().x,
                                             gameObject->transform.GetPosition().y,
                                             RtypeNetworkFactory::GetIDFromName("MonsterFlying"),
                                             getManager()->gameObjectContainer.GetServerObjectID(gameObject));
    }

}

void MonsterFlyingController::FixedUpdate()
{
    if (isServerSide()) {
        m_timer -= SaltyEngine::Engine::Instance().GetFixedDeltaTime();
        m_currDelay -= static_cast<float>(SaltyEngine::Engine::Instance().GetFixedDeltaTime());

        if (m_currDelay <= 0) {
            m_currDelay = m_minShootInterval + rand() % (int) (m_maxShootInterval - m_minShootInterval);
            Shot();
        }
//        Move();
    }
    Move();
}

void MonsterFlyingController::Move() {
    this->gameObject->transform.Translate(-(gameObject->transform.right()
                                            + SaltyEngine::Vector2(0, SaltyEngine::Mathf::Sin(gameObject->transform.GetPosition().x / 100.f
                                                                                              * SaltyEngine::Mathf::rad2deg)) )
                                          * SaltyEngine::Engine::Instance().GetFixedDeltaTime() * m_vel);
}

void MonsterFlyingController::Shot() {
    if (isServerSide()) {
        SaltyEngine::GameObject *missile = (SaltyEngine::GameObject *) SaltyEngine::Instantiate("EnemyBullet",
                                                                                                this->gameObject->transform.GetPosition(),
                                                                                                180);

        getManager()->gameObjectContainer.Add(GameObjectID::NewID(), missile);

//        BroadCastReliable<CREATEPackageGame>(
//                gameObject->transform.position.x,
//                gameObject->transform.position.y,
//                RtypeNetworkFactory::GetIDFromName("EnemyBullet"),
//                getManager()->gameObjectContainer.GetServerObjectID(missile),
//                gameObject->transform.rotation);
//
//        if (missile) {
//            MissileController *missileController = missile->GetComponent<MissileController>();
//            if (missileController != nullptr) {
//                missileController->SetTarget(
//                        SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::Player));
//            }
//        }
    }
}

void MonsterFlyingController::Die()
{
    if (!isServerSide()) {
        SaltyEngine::Instantiate("ExplosionBasic", this->gameObject->transform.GetPosition());
    }
	SaltyEngine::Object::Destroy(this->gameObject);
}

void MonsterFlyingController::TakeDamage(int amount) {
    AGenericController::TakeDamage(amount);

    if (m_health <= 0 && !m_isDead) {
        if (isServerSide()) {
            BroadCastReliable<DIEPackageGame>(
                    getManager()->gameObjectContainer.GetServerObjectID(gameObject));
            Die();
            m_isDead = true;
        }
    }
}

int MonsterFlyingController::GetHighScore() const {
    return (15);
}
