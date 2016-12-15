//
// Created by wery_a on 10/12/16.
//

#include "Prefabs/GenericController.hpp"
#include "Prefabs/MonsterWalker/MonsterWalkerController.hpp"
#include "Prefabs/Missile/Laser/LaserController.hpp"
#include "SaltyEngine/SFML.hpp"

LaserController::LaserController(SaltyEngine::GameObject *go) : SaltyEngine::SaltyBehaviour(go)
{
}

void LaserController::Start() {
    SaltyEngine::Sound::ISound *fire = SaltyEngine::SFML::AssetManager::Instance().GetSound("fire");
    fire->Play();
}

LaserController::~LaserController()
{
}

void LaserController::FixedUpdate()
{
    gameObject->transform.Translate(gameObject->transform.right() * m_vel); //* SaltyEngine::Engine::Instance().GetFixedDeltaTime());
//    std::cout << "LASER ==" << this->gameObject->transform.position << std::endl;
//    if (this->gameObject->transform.position.x > 1000) {
//        abort();
//    }
}

void LaserController::OnCollisionEnter(SaltyEngine::ICollider *col)
{
    std::cout << "colid" << std::endl;
    SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(col);
    if (!c)
        return;
    if (c->CompareTag(SaltyEngine::Layer::Tag::Enemy)) {
        AGenericController *controller = c->gameObject->GetComponent<AGenericController>();
        if (controller) {
            controller->TakeDamage(m_damage);
        }
    }
    else if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::Destroy)
    {
        SaltyEngine::Object::Destroy(this->gameObject);
    }
}