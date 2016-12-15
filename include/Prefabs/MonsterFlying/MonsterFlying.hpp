#ifdef _WIN32
    #ifdef DLL_EXPORT
        #define MONSTERFLYING_API __declspec(dllexport)
    #else
        #define MONSTERFLYING_API __declspec(dllimport)
    #endif
#else
#define MONSTERFLYING_API
#endif

#ifndef MONSTERFLYING_HPP_
#define MONSTERFLYING_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	// Cette classe est export�e de Monster.dll
	class MonsterFlying : public SaltyEngine::GameObject
	{
	public:
		MonsterFlying();
		virtual ~MonsterFlying();
	};

	SaltyEngine::Object const *GetObjectPrefab();
}

#endif