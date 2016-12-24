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
//    SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(col);
    SaltyEngine::SFML::SpriteCollider2D *c = dynamic_cast<SaltyEngine::SFML::SpriteCollider2D *>(col);

    if (!c)
        return;
    if (c->CompareTag(SaltyEngine::Layer::Tag::Enemy)) {
        AGenericController *controller = c->gameObject->GetComponent<AGenericController>();
        if (controller) {
            controller->TakeDamage(m_damage);
            this->m_targetNbr -= 1;
            if (this->m_targetNbr == 0) {
                SaltyEngine::Object::Destroy(this->gameObject);
            }
            if (playerController) {
                playerController->SetHighScore(playerController->GetHighScore() + controller->GetHighScore());
            }
        }
    }
}

//void LaserController::OnCollisionExit(SaltyEngine::ICollider *collider)
//{
//    SaltyEngine::SFML::SpriteCollider2D *c = dynamic_cast<SaltyEngine::SFML::SpriteCollider2D *>(collider);
//
//    if (!c)
//        return;
//    if (c->gameObject->GetTag() == SaltyEngine::Layer::Tag::Destroy)
//    {
//        if (playerController) {
//            playerController->SetHighScore(playerController->GetHighScore());
//        }
//        SaltyEngine::Object::Destroy(this->gameObject);
//    }
//}

void LaserController::Power(int damage) {
    std::string anim;

    //this switch case is here because we can't use a static global map
    //      --> bug observed program tries to double free this global because
    //      this file is compiled in a shared library and inside the game program
    // /!\ Do not try to change this switch case by a map
    switch (damage)
    {
        case 1:
            anim = "Laser/simple";
//            gameObject->transform.position.x += 30;
            gameObject->transform.SetPosition(gameObject->transform.GetPosition() + SaltyEngine::Vector2(30, 0));
            break;
        case 2:
//            gameObject->transform.position.x += 35;
            gameObject->transform.SetPosition(gameObject->transform.GetPosition() + SaltyEngine::Vector2(35, 0));

            anim = "Laser/power1";
            break;
        case 3:
//            gameObject->transform.position.x += 45;
            gameObject->transform.SetPosition(gameObject->transform.GetPosition() + SaltyEngine::Vector2(45, 0));

            anim = "Laser/power2";
            break;
        case 4:
//            gameObject->transform.position.x += 55;
            gameObject->transform.SetPosition(gameObject->transform.GetPosition() + SaltyEngine::Vector2(55, 0));

            anim = "Laser/power3";
            break;
        case 5:
//            gameObject->transform.position.x += 60;
            gameObject->transform.SetPosition(gameObject->transform.GetPosition() + SaltyEngine::Vector2(60, 0));

            anim = "Laser/power4";
            break;
        default:
            return;
    }
    m_damage = damage;
    m_targetNbr = damage;
    SaltyEngine::SFML::Animation *animation = gameObject->GetComponent<SaltyEngine::SFML::Animation>();
    if (animation) {
        animation->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation(anim), "Shoot");
        animation->Play("Shoot");
    }
}

void LaserController::AddPlayerController(SaltyEngine::PlayerController *playerController) {
    this->playerController = playerController;
}