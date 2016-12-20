#ifdef _WIN32
    #ifdef MONSTERNEUNOEIL_EXPORTS
        #define MONSTERNEUNOEIL_API __declspec(dllexport)
    #else
        #define MONSTERNEUNOEIL_API __declspec(dllimport)
    #endif
#else
#define MONSTERNEUNOEIL_API
#endif

#ifndef MONSTERNEUNOEIL_HPP_
#define MONSTERNEUNOEIL_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class MonsterNeunoeil : public SaltyEngine::GameObject
	{
	public:
		MonsterNeunoeil();
		virtual ~MonsterNeunoeil();
	};

	SaltyEngine::Object const *GetObjectPrefab();
}

#endif