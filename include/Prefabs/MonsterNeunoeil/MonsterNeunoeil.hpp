
#ifndef MONSTERNEUNOEIL_HPP_
#define MONSTERNEUNOEIL_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class LIB_EXPORT MonsterNeunoeil : public SaltyEngine::GameObject
	{
	public:
		MonsterNeunoeil();
		virtual ~MonsterNeunoeil();
	};

	LIB_EXPORT SaltyEngine::Object const *GetObjectPrefab();
}

#endif