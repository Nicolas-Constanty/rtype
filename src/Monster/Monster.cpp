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
}

Monster::~Monster()
{
}

MONSTER_API SaltyEngine::Object const*GetObjectPrefab()
{
	Monster *m = new Monster();
	m->AddComponent<MonsterController>();
	std::cout << "JE suis laaaaa" << std::endl;
	return m;
}
