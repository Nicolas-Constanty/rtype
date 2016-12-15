#include <Rtype/Game/Common/GameObjectID.hpp>
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include "Prefabs/Missile/MissileController.hpp"
#include "Prefabs/MonsterWalker/MonsterWalkerController.hpp"
#include "SaltyEngine/SFML.hpp"
#include "SaltyEngine/SFML/Animation.hpp"

MonsterWalkerController::MonsterWalkerController(SaltyEngine::GameObject *obj) : AGenericController("MonsterWalkerController", obj)
{
    m_health = 1;
}


MonsterWalkerController::~MonsterWalkerController()
{
}

void MonsterWalkerController::Start()
{
    LoadManager();
	m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
    m_anim = gameObject->GetComponent<SaltyEngine::SFML::Animation>();
    m_anim->Play("WalkLeft");
    m_startPoint = gameObject->transform.position;
//    SaltyEngine::GameObject *gameman = SaltyEngine::Engine::Instance().GetCurrentScene()->FindByName("GameServer");
//    if (gameman)
//        gameServer = gameman->GetComponent<Rtype::Game::Server::GameServerObject>();
}

// TODO : add jump
void MonsterWalkerController::FixedUpdate()
{
	m_currDelay -= static_cast<float>(SaltyEngine::Engine::Instance().GetFixedDeltaTime());

	if (m_currDelay <= 0)
	{
        m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
        if (isServerSide()) {
//            Shot();
        }
	}
    Move();
}

void MonsterWalkerController::Move() {
        this->gameObject->transform.Translate(-gameObject->transform.right() * m_vel);
        if (fabsf(gameObject->transform.position.x - m_startPoint.x) > m_walkDistance) {
            gameObject->transform.Rotate(180);
            PlayAnim("Walk");
        }
   // std::cout << "MnsterWalkerController ==" << this->gameObject->transform.position << std::endl;
}

void MonsterWalkerController::Shot() {
    if (!isServerSide()) {
        PlayAnim("Jump");
        PlayAnim("Walk", true);
    }

   if (isServerSide()) {
       SaltyEngine::GameObject *missile = (SaltyEngine::GameObject *) SaltyEngine::Instantiate("EnemyBullet",
                                                                                                this->gameObject->transform.position,
                                                                                                180);
       getManager()->gameObjectContainer.Add(GameObjectID::NewID(), missile);

       BroadCastReliable<ENEMYSHOTPackageGame>(
//               &Network::UDP::AUDPConnection::SendReliable<ENEMYSHOTPackageGame>,
               getManager()->gameObjectContainer.GetServerObjectID(gameObject));

       BroadCastReliable<CREATEPackageGame>(
//               &Network::UDP::AUDPConnection::SendReliable<CREATEPackageGame>,
               gameObject->transform.position.x,
               gameObject->transform.position.y,
               RtypeNetworkFactory::GetIDFromName("EnemyBullet"),
               getManager()->gameObjectContainer.GetServerObjectID(missile),
               gameObject->transform.rotation);

       if (missile) {
            MissileController *missileController = missile->GetComponent<MissileController>();
            if (missileController != nullptr) {
                missileController->SetTarget(
                        SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::Player));

            }
       }
    }
}

void MonsterWalkerController::Die() const
{
    if (!isServerSide()) {
        SaltyEngine::Instantiate("ExplosionBasic", this->gameObject->transform.position);
    }
    SaltyEngine::Object::Destroy(this->gameObject);
}

void MonsterWalkerController::TakeDamage(int amount)
{
  //  if (SaltyEngine::BINARY_ROLE == SaltyEngine::NetRole::SERVER) {
        AGenericController::TakeDamage(amount);

        if (m_health <= 0 && !m_isDead) {
            if (isServerSide()) {
                BroadCastReliable<DIEPackageGame>(
//                        &Network::UDP::AUDPConnection::SendReliable<DIEPackageGame>,
                        getManager()->gameObjectContainer.GetServerObjectID(gameObject));
                Die();
            }
            m_isDead = true;
        }
    //}
}

//void MonsterWalkerController::OnCollisionEnter(SaltyEngine::ICollider *col)
//{
//    if (col != nullptr)
//    {
//        SaltyEngine::SFML::BoxCollider2D *c = dynamic_cast<SaltyEngine::SFML::BoxCollider2D*>(col);
//        if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::BulletPlayer)
//        {
//            TakeDamage(1);
//        }
//    }
//}

void MonsterWalkerController::PlayAnim(std::string const &anim, bool queued) const
{
    if (gameObject->transform.right().x > 0)
        (!queued) ? m_anim->Play(anim + "Left") : m_anim->PlayQueued(anim + "Left");
    else
        (!queued) ? m_anim->Play(anim + "Right") : m_anim->PlayQueued(anim + "Right");
}