#include <SaltyEngine/Maths.hpp>
#include "Rtype/Game/Common/GameObjectID.hpp"
#include "Rtype/Game/Common/RtypeNetworkFactory.hpp"
#include "Prefabs/MonsterMedusa/MonsterMedusaController.hpp"

MonsterMedusaController::MonsterMedusaController(SaltyEngine::GameObject *obj) :
        AGenericController("MonsterMedusaController", obj)
{
    m_health = 100;
}


MonsterMedusaController::~MonsterMedusaController()
{
}

void MonsterMedusaController::Start()
{
    LoadManager();

    m_verticalDistance = 300;

    m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
    if (!isServerSide())
    {
        m_anim = gameObject->GetComponent<SaltyEngine::SFML::Animation>();
        m_sprr = this->gameObject->GetComponent<SaltyEngine::SFML::SpriteRenderer>();
        PlayNewBackgroundSound("r-type-boss");
    }

    if (isServerSide()) {
        BroadCastReliable<CREATEPackageGame>(gameObject->transform.GetPosition().x,
                                             gameObject->transform.GetPosition().y,
                                             RtypeNetworkFactory::GetIDFromName("MonsterMedusa"),
                                             getManager()->gameObjectContainer.GetServerObjectID(gameObject));
    }

    m_canon = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
    m_canon->transform.SetPosition(this->gameObject->transform.GetPosition());
    m_canon->transform.SetRotation(180);
    m_canon->transform.SetParent(&gameObject->transform);
}

void MonsterMedusaController::FixedUpdate()
{
    m_currTransitionDelay -= static_cast<float>(SaltyEngine::Engine::Instance().GetFixedDeltaTime());
    if (isServerSide()) {
        m_currDelay -= static_cast<float>(SaltyEngine::Engine::Instance().GetFixedDeltaTime());
        m_spawnIntervalCurr -= static_cast<float>(SaltyEngine::Engine::Instance().GetFixedDeltaTime());

        if (m_currDelay <= 0) {
            if (m_state == E_LAUNCH_SALVE)
                m_currDelay = 0.4;
            else
                m_currDelay = m_minShootInterval + rand() % (int) (m_maxShootInterval - m_minShootInterval);
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

void MonsterMedusaController::Move() {
    switch (m_state)
    {
        case E_CREATING:
            if (isServerSide() && m_spawnIntervalCurr <= 0)
            {
                m_spawnIntervalCurr = m_spawnInterval;
                // Spawns a monster in a circle arc in front of the medusa
                float rand = (std::rand() % 90 + 135) * SaltyEngine::Mathf::deg2rad;
                SaltyEngine::Vector2 coord;
                coord.x = m_canon->transform.GetPosition().x + 200 * std::cos(rand);
                coord.y = m_canon->transform.GetPosition().y + 200 * std::sin(rand);
                getManager()->gameObjectContainer.Add(GameObjectID::NewID(),
                                                      (SaltyEngine::GameObject*)SaltyEngine::Instantiate("Monster", coord));
            }
            break;
        case E_MOVING2:
        case E_MOVING:
            this->gameObject->transform.Translate(SaltyEngine::Vector2::up() * m_vel * m_dir);
            if (this->gameObject->transform.GetPosition().y <= 100)
                m_dir = 1;
            else if (this->gameObject->transform.GetPosition().y >= m_verticalDistance)
                m_dir = -1;
            break;
    }
}

void MonsterMedusaController::Shot() {
   if (isServerSide())
   {
       if (m_state == E_LAUNCH_SALVE)
       {
           --m_salveCountCurrent;
           if (m_salveCountCurrent <= 0)
           {
               m_salveCountCurrent = m_salveCount;
           }
           else
           {
               m_canon->transform.SetRotation(m_canonRot);
               m_canonRot += 10;
               SaltyEngine::GameObject *missile = (SaltyEngine::GameObject *) SaltyEngine::Instantiate("MissileMedusa",
                                                                                                       m_canon->transform.GetPosition(),
                                                                                                       m_canon->transform.GetRotation());
               getManager()->gameObjectContainer.Add(GameObjectID::NewID(), missile);

               BroadCastReliable<ENEMYSHOTPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
           }
       }
       else if (m_state == E_MOVING || m_state == E_MOVING2)
       {
           m_canonRot = 135;
           m_canon->transform.SetRotation(180);
           SaltyEngine::GameObject *missile = (SaltyEngine::GameObject *) SaltyEngine::Instantiate("MissileMedusa",
                                                                                                   m_canon->transform.GetPosition(),
                                                                                                   m_canon->transform.GetRotation());
           getManager()->gameObjectContainer.Add(GameObjectID::NewID(), missile);

           BroadCastReliable<ENEMYSHOTPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
       }
    }
}

void MonsterMedusaController::Die()
{
    if (!isServerSide())
    {
        for (int i = 0; i < 15; ++i)
        {
            SaltyEngine::Instantiate("ExplosionBasic", this->gameObject->transform.GetPosition() + SaltyEngine::Vector2(rand() % 100, rand() % 100));
        }
    }
    SaltyEngine::Object::Destroy(this->gameObject);
}

void MonsterMedusaController::TakeDamage(int amount)
{
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

void MonsterMedusaController::OnCollisionEnter(SaltyEngine::ICollider *collider) {
    SaltyEngine::SFML::SpriteCollider2D *col = dynamic_cast<SaltyEngine::SFML::SpriteCollider2D*>(collider);
    if (col)
    {
        if (!isServerSide() && col->gameObject->CompareTag(SaltyEngine::Layer::Tag::BulletPlayer))
        {
            if (!m_anim->IsPlaying("MedusaDamaged"))
                m_anim->Play("MedusaDamaged");
        }
    }
}

void MonsterMedusaController::GoToNextState()
{
    m_state++;
}
