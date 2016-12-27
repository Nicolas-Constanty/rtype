#pragma once

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class LIB_EXPORT MissileMedusa : public SaltyEngine::GameObject
	{
	public:
		MissileMedusa();
		virtual ~MissileMedusa();
	};

LIB_EXPORT	SaltyEngine::Object const*GetObjectPrefab();
}
