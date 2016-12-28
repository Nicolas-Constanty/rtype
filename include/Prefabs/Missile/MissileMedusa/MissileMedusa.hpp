#pragma once

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class PREF_EXPORT MissileMedusa : public SaltyEngine::GameObject
	{
	public:
		MissileMedusa();
		virtual ~MissileMedusa();
	};

	PREF_EXPORT	SaltyEngine::Object const*GetObjectPrefab();
}
