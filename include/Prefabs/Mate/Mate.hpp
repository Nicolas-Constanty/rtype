//
// Created by gaspar_q on 12/12/16.
//

#ifndef RTYPE_MATE_HPP
#define RTYPE_MATE_HPP

#include "SaltyEngine/SaltyEngine.hpp"
#include "SaltyEngine/GameObject.hpp"
#include <SaltyEngine/GameObject.hpp>
#include "Common/DLLexport.hpp"

extern "C"
{
    class PREF_EXPORT Mate : public SaltyEngine::GameObject
    {
    public:
        Mate();
        virtual ~Mate();
    };
	PREF_EXPORT  SaltyEngine::Object const *GetObjectPrefab();
};

#endif //RTYPE_MATE_HPP
