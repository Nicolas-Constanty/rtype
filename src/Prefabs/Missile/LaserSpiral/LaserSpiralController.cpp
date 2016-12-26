//
// Created by wery_a on 10/12/16.
//

#include "Prefabs/GenericController.hpp"
#include "Prefabs/Missile/LaserSpiral/LaserSpiralController.hpp"
#include "SaltyEngine/SFML.hpp"

LaserSpiralController::LaserSpiralController(SaltyEngine::GameObject *go) : SaltyEngine::SaltyBehaviour(go)
{
    playerController = NULL;
    soundFire = SaltyEngine::SFML::AssetManager::Instance().GetSound("Laser/fire");
}

void LaserSpiralController::Start() {
    soundFire->Play();
}

LaserSpiralController::~LaserSpiralController()
{
    delete soundFire;
}

void LaserSpiralController::FixedUpdate()
{
    gameObject->transform.Translate(gameObject->transform.right() * m_vel);
}

void LaserSpiralController::OnCollisionEnter(SaltyEngine::ICollider *col)
{
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