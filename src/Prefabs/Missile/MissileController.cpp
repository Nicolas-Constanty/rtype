#include "SaltyEngine/GameObject.hpp"
#include "Prefabs/Missile/MissileController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/Animation.hpp"

MissileController::MissileController(SaltyEngine::GameObject *go) : SaltyEngine::SaltyBehaviour(go)
{
}


MissileController::~MissileController()
{
}

void MissileController::Start() {
    SaltyEngine::Sound::ISound *fire = SaltyEngine::SFML::AssetManager::Instance().GetSound("fire");
	fire->Play();
}

void MissileController::Update()
{
    gameObject->transform.Translate(gameObject->transform.right() * m_vel * SaltyEngine::Engine::Instance().GetFixedDeltaTime());
}

void MissileController::SetTarget(SaltyEngine::GameObject const* target)
{
    if (target != nullptr)
    {
        gameObject->transform.LookAt(target->transform);
    }
}
