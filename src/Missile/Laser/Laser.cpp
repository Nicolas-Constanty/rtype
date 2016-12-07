#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "Missile/Laser/Laser.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/Debug.hpp"

Laser::Laser(SaltyEngine::GameObject * const gamObj) : SaltyEngine::SaltyBehaviour(gamObj)
{
	SaltyEngine::SFML::Texture *texture = ::SaltyEngine::SFML::AssetManager::Instance().GetTexture("Laser");
	SaltyEngine::SFML::Rect *rect = new ::SaltyEngine::SFML::Rect(201, 154, 64, 14);
	SaltyEngine::SFML::Sprite *spr = new ::SaltyEngine::SFML::Sprite(texture, rect);
	gameObject->AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, ::SaltyEngine::Layout::normal);
	gameObject->AddComponent<SaltyEngine::SFML::BoxCollider2D>();
	m_speed = 20.0f;
}

void Laser::FixedUpdate()
{
	gameObject->transform.Translate(SaltyEngine::Vector(1, 0) * m_speed);
}

void Laser::OnCollisionEnter(SaltyEngine::ICollider *col)
{
	SaltyEngine::Debug::PrintSuccess("Laser hit something");
}

Laser::~Laser()
{
}
