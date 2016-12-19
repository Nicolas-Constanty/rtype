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
    if (!isServerSide())
    {
        m_anim = gameObject->GetComponent<SaltyEngine::SFML::Animation>();
        m_anim->Play("EyeClose");
    }

    for (size_t i = 0; i < 4 ; ++i)
    {
        SaltyEngine::GameObject *go = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
        go->transform.position = this->gameObject->transform.position;
        go->transform.Rotate(90 * i);
        go->transform.position += go->transform.position.left() * 90;
        go->transform.SetParent(&this->gameObject->transform);
        SaltyEngine::SFML::Animation *animation = go->AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
        animation->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Laser/loading"), "Loading");
        m_canons[i] = go;
    }

    gameObject->transform.position = SaltyEngine::Vector2(400, 100);
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
    this->gameObject->transform.Rotate(0.1f);
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
    return;
    static int i = 0;
    this->gameObject->transform.Translate(-gameObject->transform.right() * m_vel);
    if (i % 3 == 0)
    {
        BroadcastPackage<MOVEPackageGame>(
                gameObject->transform.position.x,
                gameObject->transform.position.y,
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
       SaltyEngine::GameObject *missile = (SaltyEngine::GameObject *) SaltyEngine::Instantiate("EnemyBullet",
                                                                                                this->gameObject->transform.position,
                                                                                                180);
       getManager()->gameObjectContainer.Add(GameObjectID::NewID(), missile);

       BroadCastReliable<ENEMYSHOTPackageGame>(getManager()->gameObjectContainer.GetServerObjectID(gameObject));
    }
}

void MonsterNeunoeilController::Die() const
{
    if (!isServerSide())
    {
        SaltyEngine::Instantiate("ExplosionBasic", this->gameObject->transform.position);
    }
    SaltyEngine::Object::Destroy(this->gameObject);
}

void MonsterNeunoeilController::TakeDamage(int amount)
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

void MonsterNeunoeilController::SetInvincibility(bool invincible)
{
    m_isInvincible = invincible;
}
