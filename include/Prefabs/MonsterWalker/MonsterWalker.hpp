#ifndef MONSTERWALKER_HPP_
#define MONSTERWALKER_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class PREF_EXPORT MonsterWalker : public SaltyEngine::GameObject
	{
	public:
		MonsterWalker();
		virtual ~MonsterWalker();
	};

	PREF_EXPORT SaltyEngine::Object const *GetObjectPrefab();
}

#endif