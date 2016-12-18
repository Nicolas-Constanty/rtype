//
// Created by wery_a on 10/12/16.
//

#include "Prefabs/GenericController.hpp"
#include "Prefabs/Missile/Laser/LaserController.hpp"
#include "SaltyEngine/SFML.hpp"

LaserController::LaserController(SaltyEngine::GameObject *go) : SaltyEngine::SaltyBehaviour(go)
{
    playerController = NULL;
    soundFire = SaltyEngine::SFML::AssetManager::Instance().GetSound("Laser/fire");
}

void LaserController::Start() {
    soundFire->Play();
}

LaserController::~LaserController()
{
    delete soundFire;
}

void LaserController::FixedUpdate()
{
    gameObject->transform.Translate(gameObject->transform.right() * m_vel);
}

void LaserController::OnCollisionEnter(SaltyEngine::ICollider *col)
{
//    std::cout << "ONCOLLISION ENTER" << std::endl;
    SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(col);
    if (!c)
        return;
    if (c->CompareTag(SaltyEngine::Layer::Tag::Enemy)) {
        AGenericController *controller = c->gameObject->GetComponent<AGenericController>();
        if (controller) {
            controller->TakeDamage(m_damage);
            if (playerController) {
                playerController->SetHighScore(playerController->GetHighScore() + controller->GetHighScore());
            }
        }
    }
    this->m_damage -= 1;
    if (this->m_damage == 0) {
        std::cout << "ON VA LE DESTROY" << std::endl;
//        SaltyEngine::Object::Destroy(this->gameObject);
        std::cout << "SEG FAULT" << std::endl;
    }
}

void LaserController::OnCollisionExit(SaltyEngine::ICollider *collider)
{
    SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(collider);

    if (!c)
        return;
    if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::Destroy)
    {
//        if (playerController) {
//            playerController->SetHighScore(playerController->GetHighScore());
//        }
//        SaltyEngine::Object::Destroy(this->gameObject);
    }
}

void LaserController::Power(int damage) {
    std::string anim;
    std::cout << "lolilol" << std::endl;

    //this switch case is here because we can't use a static global map
    //      --> bug observed program tries to double free this global because
    //      this file is compiled in a shared library and inside the game program
    // /!\ Do not try to change this switch case by a map
    switch (damage)
    {
        case 1:
            anim = "Laser/simple";
            break;
        case 2:
            anim = "Laser/power1";
            break;
        case 3:
            anim = "Laser/power2";
            break;
        case 4:
            anim = "Laser/power3";
            break;
        case 5:
            anim = "Laser/power4";
            break;
        default:
            return;
    }
    m_damage = damage;
    SaltyEngine::SFML::Animation *animation = gameObject->GetComponent<SaltyEngine::SFML::Animation>();
    if (animation) {
        std::cout << "after animation" << std::endl;
        animation->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation(anim), "Shoot");
        animation->Play("Shoot");
    }
}

void LaserController::AddPlayerController(SaltyEngine::PlayerController *playerController) {
    this->playerController = playerController;
}
