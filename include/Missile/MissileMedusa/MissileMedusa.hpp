#pragma once

#ifdef _WIN32
#ifdef MISSILEMEDUSA_EXPORTS
#define MISSILEMEDUSA_API __declspec(dllexport)
#else
#define MISSILEMEDUSA_API __declspec(dllimport)
#endif
#else
#define MISSILEMEDUSA_API
#endif

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class MissileMedusa : public SaltyEngine::GameObject
	{
	public:
		MissileMedusa();
		virtual ~MissileMedusa();
	};

	MISSILEMEDUSA_API SaltyEngine::Object const*GetObjectPrefab();
}
