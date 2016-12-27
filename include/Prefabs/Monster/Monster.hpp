#ifndef MONSTER_HPP_
#define MONSTER_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	// Cette classe est export�e de Monster.dll
	class LIB_EXPORT Monster : public SaltyEngine::GameObject
	{
	public:
		Monster();
		virtual ~Monster();
	};

	//extern MONSTER_API int nMonster;

LIB_EXPORT	SaltyEngine::Object const *GetObjectPrefab();
}

#endif