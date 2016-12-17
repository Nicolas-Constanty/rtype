#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include <Rtype/Game/Common/GameObjectID.hpp>
#include "Prefabs/Missile/MissileController.hpp"
#include "Prefabs/Monster/MonsterController.hpp"
#include "SaltyEngine/SFML.hpp"

MonsterController::MonsterController(SaltyEngine::GameObject *obj) : AGenericController("MonsterController", obj)
{
    m_health = 3;
}


MonsterController::~MonsterController()
{
}

void MonsterController::Start()
{
    LoadManager();
	m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
//    SaltyEngine::GameObject *gameman = SaltyEngine::Engine::Instance().GetCurrentScene()->FindByName("GameServer");
//    if (gameman)
//        gameServer = gameman->GetComponent<Rtype::Game::Server::GameServerObject>();
}

void MonsterController::FixedUpdate()
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

void MonsterController::Move() {
    this->gameObject->transform.Translate(-gameObject->transform.right() * SaltyEngine::Engine::Instance().GetFixedDeltaTime() * m_vel);
    BroadcastPackage<MOVEPackageGame>(
            gameObject->transform.position.x,
            gameObject->transform.position.y,
            getManager()->gameObjectContainer.GetServerObjectID(gameObject));
}

void MonsterController::Shot() {
    if (isServerSide()) {
        SaltyEngine::GameObject *missile = (SaltyEngine::GameObject *) SaltyEngine::Instantiate("MissileMedusa",
                                                                                                this->gameObject->transform.position);

        getManager()->gameObjectContainer.Add(GameObjectID::NewID(), missile);

        BroadCastReliable<ENEMYSHOTPackageGame>(
                getManager()->gameObjectContainer.GetServerObjectID(gameObject));

//        BroadCastReliable<CREATEPackageGame>(
//                gameObject->transform.position.x,
//                gameObject->transform.position.y,
//                RtypeNetworkFactory::GetIDFromName("MissileMedusa"),
//                getManager()->gameObjectContainer.GetServerObjectID(missile),
//                gameObject->transform.rotation);


//        if (missile) {
//            MissileController *missileController = missile->GetComponent<MissileController>();
//            if (missileController != nullptr) {
//                missileController->SetTarget(
//                        SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::Player));
//            }
//        }
    }
}

void MonsterController::Die() const
{
    if (!isServerSide()) {
        SaltyEngine::Instantiate("ExplosionBasic", this->gameObject->transform.position);
    }
	SaltyEngine::Object::Destroy(this->gameObject);
}

void MonsterController::TakeDamage(int amount)
{
	AGenericController::TakeDamage(amount);

	if (m_health <= 0 && !m_isDead)
	{
        if (isServerSide()) {
            BroadCastReliable<DIEPackageGame>(
//                    &Network::UDP::AUDPConnection::SendReliable<DIEPackageGame>,
                    getManager()->gameObjectContainer.GetServerObjectID(gameObject));
            Die();
        }
		m_isDead = true;
	}
}

void MonsterController::OnCollisionEnter(SaltyEngine::ICollider *col)
{
//    if (col != nullptr)
//    {
//        SaltyEngine::SFML::BoxCollider2D *c = dynamic_cast<SaltyEngine::SFML::BoxCollider2D*>(col);
//        if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::BulletPlayer)
//        {
//            TakeDamage(1);
//        }
//    }
}