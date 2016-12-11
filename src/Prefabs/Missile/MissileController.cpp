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
    SaltyEngine::SFML::Texture *texture = SaltyEngine::SFML::AssetManager::Instance().GetTexture("explosion");
    if (texture != nullptr)
    {
        gameObject->AddComponent<SaltyEngine::SFML::SpriteRenderer>(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(326, 100, 65, 65)), SaltyEngine::Layout::normal);
        gameObject->AddComponent < SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
        SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(326, 100, 65, 65)));
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(326+65, 100, 65, 65)));
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(326+65+65, 100, 65, 65)));
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(326+65+65+65, 100, 65, 65)));
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(326+65+65+65+65, 100, 65, 65)));
        clip->SetFrameRate(5);

        gameObject->GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Shoot");
    }
    else
    {
        SaltyEngine::Debug::PrintWarning("MissileMedusa: could not load texture");
    }
    SaltyEngine::Sound::ISound *fire = SaltyEngine::SFML::AssetManager::Instance().GetSound("fire");
	fire->Play();
}

void MissileController::Update()
{
    gameObject->transform.Translate(gameObject->transform.right() * m_vel * SaltyEngine::SaltyEngine::Instance().GetFixedDeltaTime());
}

void MissileController::SetTarget(SaltyEngine::GameObject const* target)
{
    if (target != nullptr)
    {
        gameObject->transform.LookAt(target->transform);
//        gameObject->transform.rotation = SaltyEngine::Vector::Angle(gameObject->transform.position, target->transform.position);
    }
}
