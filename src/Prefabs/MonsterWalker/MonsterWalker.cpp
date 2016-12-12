#include "Prefabs/MonsterWalker/MonsterWalker.hpp"
#include "Prefabs/MonsterWalker/MonsterWalkerController.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/Animation.hpp"

/**
 * @brief You can add your properties here
 */
MonsterWalker::MonsterWalker() : GameObject("MonsterWalker")
{
    SaltyEngine::SFML::Texture *texture = SaltyEngine::SFML::AssetManager::Instance().GetTexture("monsterwalker");
    if (texture != nullptr)
    {
        AddComponent<SaltyEngine::SFML::SpriteRenderer>(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 0, 34, 34)), SaltyEngine::Layout::normal);
        AddComponent<SaltyEngine::Animation<sf::Vector2i>>(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
        SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>();

        // Walking clip
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 0, 34, 34)));
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(34, 0, 34, 34)));
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(68, 0, 34, 34)));
        clip->SetFrameRate(5);
        GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Walk");

        // Jumping clip
        clip = new SaltyEngine::AnimationClip<sf::Vector2i>();
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(68, 34, 34, 34)));
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(34, 34, 34, 34)));
        clip->AddSprite(new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(0, 34, 34, 34)));
        clip->SetFrameRate(5);
        GetComponent<SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Jump");
    }
    else
    {
        SaltyEngine::Debug::PrintWarning("MonsterWalker: could not load texture");
    }
    AddComponent<MonsterWalkerController>();
    AddComponent<SaltyEngine::SFML::BoxCollider2D>();
}

MonsterWalker::~MonsterWalker()
{
}

MONSTERWALKER_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new MonsterWalker();
}