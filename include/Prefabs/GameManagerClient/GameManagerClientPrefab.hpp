#ifndef RTYPE_MANAGERCLIENTPREFAB_HPP
#define RTYPE_MANAGERCLIENTPREFAB_HPP

#include "SaltyEngine/GameObject.hpp"

extern "C"
{
	class PREF_EXPORT GameManagerClientPrefab : public SaltyEngine::GameObject
	{
	public:
		GameManagerClientPrefab();
		virtual ~GameManagerClientPrefab();
	};

	PREF_EXPORT SaltyEngine::Object const *GetObjectPrefab();
};

#endif //RTYPE_MANAGERCLIENTPREFAB_HPP
