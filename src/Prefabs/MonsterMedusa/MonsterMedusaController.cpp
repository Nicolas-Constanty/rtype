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
    }

    if (isServerSide()) {
        BroadCastReliable<CREATEPackageGame>(gameObject->transform.GetPosition().x,
                                             gameObject->transform.GetPosition().y,
                                             RtypeNetworkFactory::GetIDFromName("MonsterMedusa"),
                                             getManager()->gameObjectContainer.GetServerObjectID(gameObject));
    }
}

void MonsterMedusaController::FixedUpdate()
{
    m_currTransitionDelay -= static_cast<float>(SaltyEngine::Engine::Instance().GetFixedDeltaTime());
    if (isServerSide()) {
        m_currDelay -= static_cast<float>(SaltyEngine::Engine::Instance().GetFixedDeltaTime());

        if (m_currDelay <= 0) {
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
        case E_SPAWNING:
//            break;
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
       SaltyEngine::GameObject *missile = (SaltyEngine::GameObject *) SaltyEngine::Instantiate("MissileMedusa",
                                                                                               gameObject->transform.GetPosition(),
                                                                                               gameObject->transform.GetRotation());
       getManager()->gameObjectContainer.Add(GameObjectID::NewID(), missile);

       BroadCastReliable<ENEMYSHOTPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
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
