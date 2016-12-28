#ifndef MONSTERFLYING_HPP_
#define MONSTERFLYING_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	// Cette classe est export�e de Monster.dll
	class PREF_EXPORT MonsterFlying : public SaltyEngine::GameObject
	{
	public:
		MonsterFlying();
		virtual ~MonsterFlying();
	};

	PREF_EXPORT	SaltyEngine::Object const *GetObjectPrefab();
}

#endif