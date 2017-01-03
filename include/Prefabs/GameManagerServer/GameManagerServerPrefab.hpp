#ifndef RTYPE_MANAGERSERVERPREFAB_HPP
#define RTYPE_MANAGERSERVERPREFAB_HPP

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class PREF_EXPORT GameManagerServerPrefab : public SaltyEngine::GameObject
	{
	public:
		GameManagerServerPrefab();
		virtual ~GameManagerServerPrefab();
	};

	PREF_EXPORT SaltyEngine::Object const *GetObjectPrefab();
};

#endif //RTYPE_MANAGERSERVERPREFAB_HPP
