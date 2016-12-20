//
// Created by gaspar_q on 12/12/16.
//

#include <SFML/Audio.hpp>
#include <SaltyEngine/Collider.hpp>
#include <SaltyEngine/SFML/SpriteRenderer.hpp>
#include <SaltyEngine/SFML/Animation.hpp>
#include "Prefabs/Mate/MateComponent.hpp"

MateComponent::MateComponent(SaltyEngine::GameObject * const object) : RtypePrefab("MateComponent", object)
//        SaltyEngine::SaltyBehaviour("MateComponent", object)
{

}

MateComponent::MateComponent(const std::string &name, SaltyEngine::GameObject *const gamObj) :
        RtypePrefab(name, gamObj)
{

}

MateComponent::~MateComponent()
{

}

void MateComponent::Start()
{
    LoadManager();
    if (!isServerSide())
    {
        m_beamSFX = (SaltyEngine::GameObject*)SaltyEngine::Instantiate();
        m_beamSFX->AddComponent<SaltyEngine::SFML::SpriteRenderer>(SaltyEngine::SFML::AssetManager::Instance().GetSprite("Laser/loading1"), SaltyEngine::Layout::normal);
        m_beamSFX->AddComponent<SaltyEngine::SFML::SpriteCollider2D>();
//        m_beamSFX->transform.position = (this->gameObject->transform.position + SaltyEngine::Vector(30, 3));
        m_beamSFX->transform.SetPosition(this->gameObject->transform.GetPosition() + SaltyEngine::Vector(30, 3));
        SaltyEngine::SFML::Animation *animation = m_beamSFX->AddComponent<SaltyEngine::SFML::Animation>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
        animation->AddClip(SaltyEngine::SFML::AssetManager::Instance().GetAnimation("Laser/loading"), "Loading");
        m_beamSFX->transform.SetParent(&this->gameObject->transform);
        m_beamSFX->SetActive(false);
    }
}

SaltyEngine::Component *MateComponent::CloneComponent(SaltyEngine::GameObject *const obj)
{
    return new MateComponent(obj);
}

void MateComponent::OnCollisionEnter(SaltyEngine::ICollider *collider)
{
    SaltyEngine::ACollider2D<sf::Vector2i> *c = dynamic_cast<SaltyEngine::ACollider2D<sf::Vector2i>*>(collider);

    if (c)
    {
        std::string middle = "=   Collision called on: " + c->gameObject->GetName() + "   =";
        std::string limit(middle.size(), '=');

        std::cout << limit << std::endl << middle << std::endl << limit << std::endl;
    }
}

void MateComponent::SetColor(int color) {

    std::string anim;

    anim = "SpaceShip/SpaceShip" + std::to_string(color) + "-1";
    gameObject->GetComponent<::SaltyEngine::SFML::SpriteRenderer>()->SetSprite(SaltyEngine::SFML::AssetManager::Instance().GetSprite(anim));
}
