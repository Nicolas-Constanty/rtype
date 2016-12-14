#ifdef _WIN32
    #ifdef EXPLOSIONBASIC_EXPORTS
        #define EXPLOSIONBASIC_API __declspec(dllexport)
    #else
        #define EXPLOSIONBASIC_API __declspec(dllimport)
    #endif
#else
#define EXPLOSIONBASIC_API
#endif

#ifndef EXPLOSIONBASIC_HPP_
#define EXPLOSIONBASIC_HPP_

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class ExplosionBasic : public SaltyEngine::GameObject
	{
	public:
		ExplosionBasic();
		virtual ~ExplosionBasic();
	};

	EXPLOSIONBASIC_API SaltyEngine::Object const *GetObjectPrefab();
}

#endif