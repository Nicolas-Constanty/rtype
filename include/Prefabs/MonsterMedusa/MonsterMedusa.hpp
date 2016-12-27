
#ifndef MONSTERMEDUSA_HPP_
#define MONSTERMEDUSA_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class LIB_EXPORT MonsterMedusa : public SaltyEngine::GameObject
	{
	public:
		MonsterMedusa();
		virtual ~MonsterMedusa();
	};

	LIB_EXPORT SaltyEngine::Object const *GetObjectPrefab();
}

#endif