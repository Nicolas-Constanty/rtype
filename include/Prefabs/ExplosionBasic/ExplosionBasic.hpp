#ifndef EXPLOSIONBASIC_HPP_
#define EXPLOSIONBASIC_HPP_

#include "SaltyEngine/GameObject.hpp"
#include "Common/DLLexport.hpp"

extern "C"
{
	class LIB_EXPORT ExplosionBasic : public SaltyEngine::GameObject
	{
	public:
		ExplosionBasic();
		virtual ~ExplosionBasic();
	};

LIB_EXPORT	SaltyEngine::Object const *GetObjectPrefab();
}

#endif