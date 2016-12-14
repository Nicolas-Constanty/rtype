#ifdef _WIN32
    #ifdef MONSTERWALKER_EXPORTS
        #define MONSTERWALKER_API __declspec(dllexport)
    #else
        #define MONSTERWALKER_API __declspec(dllimport)
    #endif
#else
#define MONSTERWALKER_API
#endif

#ifndef MONSTERWALKER_HPP_
#define MONSTERWALKER_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class MonsterWalker : public SaltyEngine::GameObject
	{
	public:
		MonsterWalker();
		virtual ~MonsterWalker();
	};

	MONSTERWALKER_API SaltyEngine::Object const *GetObjectPrefab();
}

#endif