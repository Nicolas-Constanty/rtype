#include "Prefabs/Monster/Monster.hpp"
#include "Prefabs/Monster/MonsterController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/Animation.hpp"

/**
 * \brief You can add your properties here
 */
Monster::Monster() : GameObject("Monster")
{
    SaltyEngine::SFML::Texture *texture = SaltyEngine::SFML::AssetManager::Instance().GetTexture("monster");
    if (texture != nullptr)
    {
        AddComponent<SaltyEngine::SFML::SpriteRenderer>(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 0, 34, 34)), SaltyEngine::Layout::normal);
        AddComponent < SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
        SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 0, 34, 34)));
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(34, 0, 34, 34)));
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(68, 0, 34, 34)));
        clip->SetFrameRate(5);
        GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Walk");
    }
    else
    {
        SaltyEngine::Debug::PrintWarning("Monster: could not load texture");
    }
    AddComponent<MonsterController>();
    AddComponent<SaltyEngine::SFML::BoxCollider2D>();
}

Monster::~Monster()
{
}

MONSTER_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new Monster();
}
