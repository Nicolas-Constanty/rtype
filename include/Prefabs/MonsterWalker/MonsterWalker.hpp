#ifndef MONSTERWALKER_HPP_
#define MONSTERWALKER_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class LIB_EXPORT MonsterWalker : public SaltyEngine::GameObject
	{
	public:
		MonsterWalker();
		virtual ~MonsterWalker();
	};

	LIB_EXPORT SaltyEngine::Object const *GetObjectPrefab();
}

#endif