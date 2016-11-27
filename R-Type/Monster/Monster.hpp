// Le bloc ifdef suivant est la fa�on standard de cr�er des macros qui facilitent l'exportation 
// � partir d'une DLL. Tous les fichiers contenus dans cette DLL sont compil�s avec le symbole MONSTER_EXPORTS
// d�fini sur la ligne de commande. Ce symbole ne doit pas �tre d�fini pour un projet
// qui utilisent cette DLL. De cette mani�re, les autres projets dont les fichiers sources comprennent ce fichier consid�rent les fonctions 
// MONSTER_API comme �tant import�es � partir d'une DLL, tandis que cette DLL consid�re les symboles
// d�finis avec cette macro comme �tant export�s.
#ifdef _WIN32
    #ifdef MONSTER_EXPORTS
        #define MONSTER_API __declspec(dllexport)
    #else
        #define MONSTER_API __declspec(dllimport)
    #endif
#else
#define MONSTER_API
#endif

#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	// Cette classe est export�e de Monster.dll
	class Monster : public SaltyEngine::GameObject
	{
	public:
		Monster();
		virtual ~Monster();
	};

	//extern MONSTER_API int nMonster;

	MONSTER_API SaltyEngine::Object *GetObjectPrefab();
}

#endif