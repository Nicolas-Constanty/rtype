// Monster.cpp�: d�finit les fonctions export�es pour l'application DLL.
//

#include "Monster/Monster.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Monster/MonsterController.hpp"
#include "SaltyEngine/SFML/Sprite.hpp"
#include "SaltyEngine/Debug.hpp"

// Il s'agit d'un exemple de variable export�e
//MONSTER_API int nMonster=0;

/**
 * \brief You can add your properties here
 */
Monster::Monster() : GameObject("Monster")
{
	// Behaviour
	AddComponent<MonsterController>();

	SaltyEngine::SFML::Texture *texture = new SaltyEngine::SFML::Texture();
	if (!texture->loadFromFile("../../Assets/Textures/Image.png"))
	{
		SaltyEngine::Debug::PrintError("Failed to load texture");
	}
	else
	{
		SaltyEngine::SFML::Rect *rect = new SaltyEngine::SFML::Rect(10, 10, 100, 100);
		SaltyEngine::SFML::Sprite *spr = new SaltyEngine::SFML::Sprite(texture, rect);
		AddComponent<SaltyEngine::SFML::Sprite>(spr);
	}
}

Monster::~Monster()
{
}

MONSTER_API SaltyEngine::Object const*GetObjectPrefab()
{
	return new Monster();
}
