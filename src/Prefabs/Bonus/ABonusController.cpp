//
// Created by gaspar_q on 12/26/16.
//

#include <Prefabs/Bonus/ABonusController.hpp>

ABonusController::ABonusController(std::string const &name, SaltyEngine::GameObject *object) :
    RtypePrefab(name, object)
{

}

ABonusController::~ABonusController()
{

}

void ABonusController::OnCollisionEnter(SaltyEngine::ICollider *collider)
{
    SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(collider);

    if (!c || c->gameObject->GetTag() != SaltyEngine::Layer::Tag::Player)
        return;
    if (isServerSide())
        ExecuteBonus(c->gameObject);
    else {
        SaltyEngine::Sound::ISound *sound = SaltyEngine::SFML::AssetManager::Instance().GetSound("Coin_Drop");
        sound->Play();
    }
    Destroy(gameObject);
}

void ABonusController::Start()
{
    LoadManager();
}
