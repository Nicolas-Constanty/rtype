#ifndef MONSTERFLYING_HPP_
#define MONSTERFLYING_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	// Cette classe est export�e de Monster.dll
	class LIB_EXPORT MonsterFlying : public SaltyEngine::GameObject
	{
	public:
		MonsterFlying();
		virtual ~MonsterFlying();
	};

LIB_EXPORT	SaltyEngine::Object const *GetObjectPrefab();
}

#endif