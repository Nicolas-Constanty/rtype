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
	m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
    m_anim = gameObject->GetComponent<SaltyEngine::SFML::Animation>();
    m_anim->Play("WalkLeft");
    m_startPoint = gameObject->transform.position;
}

// TODO : add jump
void MonsterWalkerController::Update()
{
	m_currDelay -= SaltyEngine::Engine::Instance().GetDeltaTime();

	if (m_currDelay <= 0)
	{
        m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
        SaltyEngine::GameObject *missile = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("EnemyBullet", this->gameObject->transform.position, 180);
        PlayAnim("Jump");
        PlayAnim("Walk", true);

        if (missile) {
            MissileController *missileController = missile->GetComponent<MissileController>();
            if (missileController != nullptr) {
                missileController->SetTarget(SaltyEngine::GameObject::FindGameObjectWithTag(SaltyEngine::Layer::Tag::Player));
            }
        }
	}
	this->gameObject->transform.Translate(-gameObject->transform.right() * SaltyEngine::Engine::Instance().GetDeltaTime() * m_vel);
    if (fabsf(gameObject->transform.position.x - m_startPoint.x) > m_walkDistance)
    {
        gameObject->transform.Rotate(180);
        PlayAnim("Walk");
    }
}

void MonsterWalkerController::Die() const
{
    SaltyEngine::Instantiate("ExplosionBasic", this->gameObject->transform.position);
	SaltyEngine::Object::Destroy(this->gameObject);
}

void MonsterWalkerController::TakeDamage(int amount)
{
	AGenericController::TakeDamage(amount);

	if (m_health <= 0 && !m_isDead)
	{
		Die();
		m_isDead = true;
	}
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