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

	MONSTER_API SaltyEngine::Object const *GetObjectPrefab();
}

#endif