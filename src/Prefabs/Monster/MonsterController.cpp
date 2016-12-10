#include <Prefabs/Missile/MissileController.hpp>
#include "Prefabs/Monster/MonsterController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/Animation.hpp"

MonsterController::MonsterController(SaltyEngine::GameObject *obj) : SaltyEngine::SaltyBehaviour(obj)
{
}


MonsterController::~MonsterController()
{
}

void MonsterController::Start()
{
	m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
	SaltyEngine::SFML::Texture *texture = SaltyEngine::SFML::AssetManager::Instance().GetTexture("monster");
	if (texture != nullptr)
	{
		gameObject->AddComponent<SaltyEngine::SFML::SpriteRenderer>(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 0, 34, 34)), SaltyEngine::Layout::normal);
		gameObject->AddComponent < SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
		SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
		clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 0, 34, 34)));
		clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(34, 0, 34, 34)));
		clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(68, 0, 34, 34)));
		clip->SetFrameRate(5);
		gameObject->GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Walk");
	}
	else
	{
		SaltyEngine::Debug::PrintWarning("Monster: could not load texture");
	}
}

void MonsterController::Update()
{
	m_currDelay -= SaltyEngine::SaltyEngine::Instance().GetDeltaTime();

	if (m_currDelay <= 0)
	{
        m_currDelay = m_minShootInterval + rand() % (int)(m_maxShootInterval - m_minShootInterval);
        std::cout << "SHOOT ! " << std::endl;
        SaltyEngine::GameObject *missile = (SaltyEngine::GameObject*)SaltyEngine::Instantiate("MissileMedusa", this->gameObject->transform.position);
        if (missile) {
            MissileController *missileController = missile->GetComponent<MissileController>();
            if (missileController != nullptr) {
                // TODO : target player
                missileController->SetTarget(SaltyEngine::Vector(this->gameObject->transform.position.x * -100, this->gameObject->transform.position.y));
            }
            *Singleton<::SaltyEngine::SaltyEngine>::Instance().GetCurrentScene() << missile;
        }
	}
	this->gameObject->transform.Translate(SaltyEngine::Vector(-1, 0) * SaltyEngine::SaltyEngine::Instance().GetDeltaTime() * m_vel);
}

void MonsterController::Die() const
{
    SaltyEngine::Object::Destroy(this->gameObject);
    SaltyEngine::Instantiate("ExplosionMonster", this->gameObject->transform.position);
}

void MonsterController::TakeDamage(int amount)
{
	AGenericController::TakeDamage(amount);

	if (m_health <= 0 && !m_isDead)
	{
		Die();
		m_isDead = true;
	}
}