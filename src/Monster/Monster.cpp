// Monster.cpp�: d�finit les fonctions export�es pour l'application DLL.
//

#include <SFML/Graphics.hpp>
#include "Monster/Monster.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Monster/MonsterController.hpp"
#include "SaltyEngine/Config.hpp"
#include "SaltyEngine/AnimationClip.hpp"
#include "SaltyEngine/SFML/SpriteRenderer.hpp"
#include "SaltyEngine/Animation.hpp"
#include "SaltyEngine/SFML/AssetManager.hpp"

/**
 * \brief You can add your properties here
 */
Monster::Monster() : GameObject("Monster")
{
	SaltyEngine::SFML::Texture *texture = SaltyEngine::SFML::AssetManager::Instance().GetTexture("MonsterTexture");
    if (texture)
    {
        SaltyEngine::SFML::Sprite *spr = new SaltyEngine::SFML::Sprite(texture);
        this->AddComponent<SaltyEngine::SFML::SpriteRenderer>(spr, SaltyEngine::Layout::normal);
        SaltyEngine::AnimationClip<sf::Vector2i> *clip = new SaltyEngine::AnimationClip<sf::Vector2i>("WalkAnim", 10);
        for (int i = 0; i < 5; ++i)
        {
            *clip << new SaltyEngine::SFML::Sprite(texture, new SaltyEngine::SFML::Rect(10 * i, 10 * i, 100, 100));
        }
        this->AddComponent < SaltyEngine::Animation<sf::Vector2i> >(true, SaltyEngine::AnimationConstants::WrapMode::LOOP);
        this->GetComponent< SaltyEngine::Animation<sf::Vector2i> >()->AddClip(clip, "Walk");

    } else {
        SaltyEngine::Debug::PrintWarning("Monster: could not load texture");
    }
	AddComponent<MonsterController>();
}

Monster::~Monster()
{
}

MONSTER_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new Monster();
}
