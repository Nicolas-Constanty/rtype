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

    m_verticalDistance = 300;

    m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
    if (!isServerSide())
    {
        m_anim = gameObject->GetComponent<SaltyEngine::SFML::Animation>();

        m_anim->GetClip("EyeClose")->AddEvent(std::bind(&MonsterNeunoeilController::SetInvincibility, this, true));
        m_anim->GetClip("EyeOpen")->AddEvent(std::bind(&MonsterNeunoeilController::SetInvincibility, this, false));
        m_anim->Play("EyeBlink");
    }

    for (size_t i = 0; i < 4 ; ++i)
    {
        SaltyEngine::GameObject *go = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
        go->transform.SetPosition(this->gameObject->transform.GetPosition());
        go->transform.SetRotation(90 * i);
        go->transform.SetPosition(go->transform.GetPosition() + go->transform.right() * 110);
        go->transform.SetParent(&this->gameObject->transform);
        SaltyEngine::SFML::Animation *animation = go->AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
        animation->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Laser/loading"), "Loading");
        m_canons[i] = go;
    }

    gameObject->transform.SetPosition(SaltyEngine::Vector2(800, 100));
    m_startPoint = gameObject->transform.GetPosition();

    if (isServerSide()) {
        BroadCastReliable<CREATEPackageGame>(gameObject->transform.GetPosition().x,
                                             gameObject->transform.GetPosition().y,
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
    }
    Move();
}

void MonsterNeunoeilController::Move() {
    static int i = 0;
    if (m_eyeState == E_STATIC)
    {
        this->gameObject->transform.Translate(SaltyEngine::Vector2::up() * m_vel * m_dir);
        if (this->gameObject->transform.GetPosition().y <= 100)
            m_dir = 1;
        else if (this->gameObject->transform.GetPosition().y >= m_verticalDistance)
            m_dir = -1;
    }
    else if (m_eyeState == E_MOVING)
    {
        this->gameObject->transform.Rotate(0.7f);
        this->gameObject->transform.Translate(-SaltyEngine::Vector2::left() * m_vel * m_dir);
        if (this->gameObject->transform.GetPosition().x <= 100)
            m_dir = 1;
        else if (this->gameObject->transform.GetPosition().x >= m_horizontalDistance)
            m_dir = -1;
    }

    if (i % 60 == 0)
    {
        BroadcastPackage<MOVEPackageGame>(
                gameObject->transform.GetPosition().x,
                gameObject->transform.GetPosition().y,
                getManager()->gameObjectContainer.GetServerObjectID(gameObject));
    }
    ++i;
}

void MonsterNeunoeilController::Shot() {
//    if (!isServerSide()) {
//        PlayAnim("Jump");
//        PlayAnim("Walk", true);
//    }

   if (isServerSide())
   {
       if (m_eyeState == E_STATIC)
       {
           SaltyEngine::GameObject *missile = (SaltyEngine::GameObject *) SaltyEngine::Instantiate("EnemyBullet",
                                                                                                   m_canons[3]->transform.GetPosition(),
                                                                                                   m_canons[3]->transform.GetRotation());
           getManager()->gameObjectContainer.Add(GameObjectID::NewID(), missile);

           BroadCastReliable<ENEMYSHOTPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
       }
       else if (m_eyeState == E_MOVING)
       {
           for (int i = 0; i < 4; ++i)
           {
               SaltyEngine::GameObject *missile = (SaltyEngine::GameObject *) SaltyEngine::Instantiate("EnemyBullet",
                                                                                                       m_canons[i]->transform.GetPosition(),
                                                                                                       m_canons[i]->transform.GetRotation());
               getManager()->gameObjectContainer.Add(GameObjectID::NewID(), missile);

               BroadCastReliable<ENEMYSHOTPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
           }
       }
    }
}

void MonsterNeunoeilController::Die()
{
    if (!isServerSide())
    {
        for (int i = 0; i < 15; ++i)
        {
            SaltyEngine::Instantiate("ExplosionBasic", this->gameObject->transform.GetPosition() + SaltyEngine::Vector2(rand() % 100, rand() % 100));
        }
        for (int i = 0; i < 4; ++i) {
            SaltyEngine::Object::Destroy(m_canons[i]);
        }
    }
    SaltyEngine::Object::Destroy(this->gameObject);
}

void MonsterNeunoeilController::TakeDamage(int amount)
{
    if (m_isInvincible)
        return;

    AGenericController::TakeDamage(amount);

    if (m_health <= 0 && !m_isDead)
    {
        if (isServerSide())
        {
            BroadCastReliable<DIEPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
            Die();
        }
        m_isDead = true;
    }
}

void MonsterNeunoeilController::SetInvincibility(bool invincible)
{
    m_isInvincible = invincible;
}

void MonsterNeunoeilController::OnCollisionEnter(SaltyEngine::ICollider *collider) {
    SaltyEngine::SFML::SpriteCollider2D *col = dynamic_cast<SaltyEngine::SFML::SpriteCollider2D*>(collider);
    if (col)
    {
        if (m_isInvincible && col->gameObject->CompareTag(SaltyEngine::Layer::Tag::BulletPlayer))
        {
            SaltyEngine::Instantiate("ExplosionBasic", col->gameObject->transform.GetPosition());
            Destroy(col->gameObject);
//            if (isServerSide())
//            {
//                SendPackage<CREATEPackageGame>(&Network::UDP::AUDPConnection::SendReliable<CREATEPackageGame>,
//                                               gameObject->transform.position.x,
//                                               gameObject->transform.position.y,
//                                               RtypeNetworkFactory::GetIDFromName("ExplosionBasic"),
//                                               getManager()->gameObjectContainer.GetServerObjectID(gameObject));
//            }
        }
    }
}
