// Monster.cpp�: d�finit les fonctions export�es pour l'application DLL.
//

#include "Monster.hpp"
#include "SaltyEngine/GameObject.hpp"


// Il s'agit d'un exemple de variable export�e
MONSTER_API int nMonster=0;

// Il s'agit d'un exemple de fonction export�e.
MONSTER_API int fnMonster(void)
{
	SaltyEngine::GameObject *go = new SaltyEngine::GameObject("toto");
    return 42;
}

// Il s'agit du constructeur d'une classe qui a �t� export�e.
// consultez Monster.h pour la d�finition de la classe
CMonster::CMonster()
{
    return;
}
