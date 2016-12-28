//
// Created by gaspar_q on 12/16/16.
//

#ifndef RTYPE_POD_HPP
#define RTYPE_POD_HPP

#include <SaltyEngine/GameObject.hpp>

extern "C"
{
    class PREF_EXPORT Pod : public SaltyEngine::GameObject
    {
    public:
        Pod();
        virtual ~Pod();
    };

	PREF_EXPORT SaltyEngine::Object const *GetObjectPrefab();
};


#endif //RTYPE_POD_HPP
