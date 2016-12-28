#ifndef EXPLOSIONBASIC_HPP_
#define EXPLOSIONBASIC_HPP_

#include "SaltyEngine/GameObject.hpp"
#include "Common/DLLexport.hpp"

extern "C"
{
	class PREF_EXPORT ExplosionBasic : public SaltyEngine::GameObject
	{
	public:
		ExplosionBasic();
		virtual ~ExplosionBasic();
	};

	PREF_EXPORT	SaltyEngine::Object const *GetObjectPrefab();
}

#endif