// Monster.cpp�: d�finit les fonctions export�es pour l'application DLL.
//

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

MONSTER_API SaltyEngine::Object *GetMonster()
{
	return new Monster();
}
