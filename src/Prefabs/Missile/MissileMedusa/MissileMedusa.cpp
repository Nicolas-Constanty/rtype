#include "SaltyEngine/SFML/Texture.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/Animation.hpp"
#include "Prefabs/Missile/MissileMedusa/MissileMedusa.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "Prefabs/Missile/MissileController.hpp"

MissileMedusa::MissileMedusa() : GameObject("MissileMedusa")
{
    SaltyEngine::SFML::Texture *texture = SaltyEngine::SFML::AssetManager::Instance().GetTexture("Laser");
    if (texture != nullptr)
    {
        SaltyEngine::SFML::Rect *rect = new ::SaltyEngine::SFML::Rect(201, 154, 64, 14);
        SaltyEngine::SFML::Sprite *spr = new ::SaltyEngine::SFML::Sprite(texture, rect);
        AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, ::SaltyEngine::Layout::normal);

//        AddComponent<SaltyEngine::SFML::SpriteRenderer>(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 0, 34, 34)), SaltyEngine::Layout::normal);
//        AddComponent < SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
//        SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
//        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(270-150, 70, 30, 20)));
//        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(270-120, 70, 30, 20)));
//        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(270-90, 70, 30, 20)));
//        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(270-60, 70, 30, 20)));
//        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(270-30, 70, 30, 20)));
//        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(270, 70, 30, 20)));
//        clip->SetFrameRate(20);

//        AddComponent<SaltyEngine::SFML::SpriteRenderer>(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 0, 34, 34)), SaltyEngine::Layout::normal);
//        AddComponent < SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::ONCE);
//        SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
//        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 0, 34, 34)));
//        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(34, 0, 34, 34)));
//        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(68, 0, 34, 34)));
//        clip->SetFrameRate(5);
//        GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Shoot");
    }
    else
    {
        SaltyEngine::Debug::PrintWarning("MissileMedusa: could not load texture");
    }
	AddComponent<MissileController>();
}


MissileMedusa::~MissileMedusa()
{
}

MISSILEMEDUSA_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new MissileMedusa();
}
