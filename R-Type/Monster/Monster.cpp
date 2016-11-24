// Monster.cpp : définit les fonctions exportées pour l'application DLL.
//

#include "Monster.hpp"
#include "SaltyEngine/GameObject.hpp"


// Il s'agit d'un exemple de variable exportée
MONSTER_API int nMonster=0;

// Il s'agit d'un exemple de fonction exportée.
MONSTER_API int fnMonster(void)
{
	SaltyEngine::GameObject *go = new SaltyEngine::GameObject("toto");
    return 42;
}

// Il s'agit du constructeur d'une classe qui a été exportée.
// consultez Monster.h pour la définition de la classe
CMonster::CMonster()
{
    return;
}
