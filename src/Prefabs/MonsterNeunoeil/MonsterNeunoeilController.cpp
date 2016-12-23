#include <Rtype/Game/Common/GameObjectID.hpp>
#include <Rtype/Game/Common/RtypeNetworkFactory.hpp>
#include <Prefabs/Player/PlayerController.hpp>
#include "Prefabs/MonsterNeunoeil/MonsterNeunoeilController.hpp"

MonsterNeunoeilController::MonsterNeunoeilController(SaltyEngine::GameObject *obj) :
        AGenericController("MonsterNeunoeilController", obj)
{
    m_health = 100;
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
        m_anim->Play("EyeClose");
    }

    for (size_t i = 0; i < 4 ; ++i)
    {
        SaltyEngine::GameObject *go = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
        go->transform.SetPosition(this->gameObject->transform.GetPosition());
        go->transform.SetRotation(90 * i);
        go->transform.SetPosition(go->transform.GetPosition() + go->transform.right() * 110);
        go->transform.SetParent(&this->gameObject->transform);
//        SaltyEngine::SFML::Animation *animation = go->AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
//        animation->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Laser/loading"), "Loading");
        m_canons[i] = go;
    }

    gameObject->transform.SetPosition(SaltyEngine::Vector2(800, 100));

    if (isServerSide()) {
        BroadCastReliable<CREATEPackageGame>(gameObject->transform.GetPosition().x,
                                             gameObject->transform.GetPosition().y,
                                             RtypeNetworkFactory::GetIDFromName("MonsterNeunoeil"),
                                             getManager()->gameObjectContainer.GetServerObjectID(gameObject));
    }
}

void MonsterNeunoeilController::FixedUpdate()
{
    m_currTransitionDelay -= static_cast<float>(SaltyEngine::Engine::Instance().GetFixedDeltaTime());
    if (isServerSide()) {
        m_currDelay -= static_cast<float>(SaltyEngine::Engine::Instance().GetFixedDeltaTime());

        if (m_currDelay <= 0) {
            m_currDelay = m_minShootInterval + rand() % (int) (m_maxShootInterval - m_minShootInterval);
            if (!m_isInvincible)
                Shot();
        }
    }
    if (m_currTransitionDelay <= 0)
    {
        m_currTransitionDelay = m_transitionDelay;
        GoToNextState();
    }
    Move();
}

void MonsterNeunoeilController::Move() {
    switch (m_state)
    {
        case E_STATIC:
            this->gameObject->transform.Rotate(-this->gameObject->transform.GetRotation());
            this->gameObject->transform.Translate(SaltyEngine::Vector2::up() * m_vel * m_dir);
            if (this->gameObject->transform.GetPosition().y <= 200)
                m_dir = 1;
            else if (this->gameObject->transform.GetPosition().y >= 300)
                m_dir = -1;
            break;
        case E_MOVING1:
            this->gameObject->transform.Translate(SaltyEngine::Vector2::up() * m_vel * m_dir);
            if (this->gameObject->transform.GetPosition().y <= 100)
                m_dir = 1;
            else if (this->gameObject->transform.GetPosition().y >= m_verticalDistance)
                m_dir = -1;
            break;
        case E_MOVING2:
            this->gameObject->transform.Rotate(1.2f);
            this->gameObject->transform.Translate(-SaltyEngine::Vector2::left() * m_vel * m_dir * 2);
            if (this->gameObject->transform.GetPosition().x <= 100)
                m_dir = 1;
            else if (this->gameObject->transform.GetPosition().x >= m_horizontalDistance)
                m_dir = -1;
            break;
    }
}

void MonsterNeunoeilController::Shot() {
   if (isServerSide())
   {
       if (m_state == E_MOVING1)
       {
           SaltyEngine::GameObject *missile = (SaltyEngine::GameObject *) SaltyEngine::Instantiate("MissileNeunoeil",
                                                                                                   m_canons[2]->transform.GetPosition(),
                                                                                                   m_canons[2]->transform.GetRotation());
           getManager()->gameObjectContainer.Add(GameObjectID::NewID(), missile);

           BroadCastReliable<ENEMYSHOTPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
       }
       else if (m_state == E_MOVING2)
       {
           for (int i = 0; i < 4; ++i)
           {
               SaltyEngine::GameObject *missile = (SaltyEngine::GameObject *) SaltyEngine::Instantiate("MissileNeunoeil",
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
        }
        if (isServerSide() && col->gameObject->CompareTag(SaltyEngine::Layer::Tag::Player))
        {
            SaltyEngine::PlayerController *controller = col->gameObject->GetComponent<SaltyEngine::PlayerController>();
            if (controller)
            {
                controller->TakeDamage(1);
            }
        }
    }
}

void MonsterNeunoeilController::GoToNextState()
{
    m_state++;

    if (!isServerSide())
    {
        if (m_state == E_STATIC)
            m_anim->Play("EyeClose");
        if (m_state == E_MOVING1 || m_state == E_MOVING2)
            m_anim->Play("EyeOpen");
    }
}
