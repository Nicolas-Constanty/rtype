
#ifndef MONSTERNEUNOEIL_HPP_
#define MONSTERNEUNOEIL_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class PREF_EXPORT MonsterNeunoeil : public SaltyEngine::GameObject
	{
	public:
		MonsterNeunoeil();
		virtual ~MonsterNeunoeil();
	};

	PREF_EXPORT SaltyEngine::Object const *GetObjectPrefab();
}

#endif