#ifndef RTYPE_MANAGERPREFAB_HPP
#define RTYPE_MANAGERPREFAB_HPP

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class PREF_EXPORT GameManagerPrefab : public SaltyEngine::GameObject
	{
	public:
		GameManagerPrefab();
		virtual ~GameManagerPrefab();
	};

	PREF_EXPORT SaltyEngine::Object const *GetObjectPrefab();
};

#endif //RTYPE_MANAGERPREFAB_HPP
