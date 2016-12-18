#include <Rtype/Game/Common/GameObjectID.hpp>
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include "Prefabs/Missile/MissileController.hpp"
#include "Prefabs/MonsterNeunoeil/MonsterNeunoeilController.hpp"
#include "SaltyEngine/SFML.hpp"

MonsterNeunoeilController::MonsterNeunoeilController(SaltyEngine::GameObject *obj) :
        AGenericController("MonsterNeunoeilController", obj)
{
    m_health = 1;
}


MonsterNeunoeilController::~MonsterNeunoeilController()
{
}

void MonsterNeunoeilController::Start()
{
    LoadManager();
	m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
    if (!isServerSide()) {
//        m_anim = gameObject->GetComponent<SaltyEngine::SFML::Animation>();
//        m_anim->Play("WalkLeft");
    }
    m_startPoint = gameObject->transform.position;
    if (isServerSide()) {
        BroadCastReliable<CREATEPackageGame>(gameObject->transform.position.x,
                                             gameObject->transform.position.y,
                                             RtypeNetworkFactory::GetIDFromName("MonsterNeunoeil"),
                                             getManager()->gameObjectContainer.GetServerObjectID(gameObject));
    }
}

void MonsterNeunoeilController::FixedUpdate()
{
    if (isServerSide()) {
        m_currDelay -= static_cast<float>(SaltyEngine::Engine::Instance().GetFixedDeltaTime());

        if (m_currDelay <= 0) {
            m_currDelay = m_minShootInterval + rand() % (int) (m_maxShootInterval - m_minShootInterval);
            Shot();
        }
        Move();
    }
}

void MonsterNeunoeilController::Move() {
    this->gameObject->transform.Translate(-gameObject->transform.right() * m_vel);
    BroadcastPackage<MOVEPackageGame>(
            gameObject->transform.position.x,
            gameObject->transform.position.y,
            getManager()->gameObjectContainer.GetServerObjectID(gameObject));
}

void MonsterNeunoeilController::Shot() {
//    if (!isServerSide()) {
//        PlayAnim("Jump");
//        PlayAnim("Walk", true);
//    }

   if (isServerSide()) {
       SaltyEngine::GameObject *missile = (SaltyEngine::GameObject *) SaltyEngine::Instantiate("EnemyBullet",
                                                                                                this->gameObject->transform.position,
                                                                                                180);
       getManager()->gameObjectContainer.Add(GameObjectID::NewID(), missile);

       BroadCastReliable<ENEMYSHOTPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
    }
}

void MonsterNeunoeilController::Die() const
{
    if (!isServerSide()) {
        SaltyEngine::Instantiate("ExplosionBasic", this->gameObject->transform.position);
    }
    SaltyEngine::Object::Destroy(this->gameObject);
}

void MonsterNeunoeilController::TakeDamage(int amount)
{
    AGenericController::TakeDamage(amount);

    if (m_health <= 0 && !m_isDead) {
        if (isServerSide()) {
            BroadCastReliable<DIEPackageGame>(
                    getManager()->gameObjectContainer.GetServerObjectID(gameObject));
            Die();
        }
        m_isDead = true;
    }
}