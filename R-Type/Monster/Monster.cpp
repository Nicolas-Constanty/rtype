// Monster.cpp�: d�finit les fonctions export�es pour l'application DLL.
//

#include "stdafx.h"
#include "Monster.hpp"
#include "SaltyEngine/GameObject.hpp"

// Il s'agit d'un exemple de variable export�e
//MONSTER_API int nMonster=0;

/**
 * \brief You can add your properties here
 */
Monster::Monster() : GameObject("Monster")
{
}

Monster::~Monster()
{
}

MONSTER_API std::unique_ptr<SaltyEngine::Object> GetMonster()
{
	return std::unique_ptr<SaltyEngine::Object>(new Monster());
}
