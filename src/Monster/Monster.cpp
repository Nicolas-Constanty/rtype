// Monster.cpp�: d�finit les fonctions export�es pour l'application DLL.
//

#include "Monster/Monster.hpp"
#include "SaltyEngine/GameObject.hpp"
#include "Monster/MonsterController.hpp"

// Il s'agit d'un exemple de variable export�e
//MONSTER_API int nMonster=0;

/**
 * \brief You can add your properties here
 */
Monster::Monster() : GameObject("Monster")
{
	AddComponent<MonsterController>();
}

Monster::~Monster()
{
}

MONSTER_API SaltyEngine::Object *GetObjectPrefab()
{
	return new Monster();
}
