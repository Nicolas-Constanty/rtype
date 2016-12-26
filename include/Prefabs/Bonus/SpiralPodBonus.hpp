//
// Created by gaspar_q on 12/26/16.
//

#ifndef RTYPE_SPIRALPODBONUS_HPP
#define RTYPE_SPIRALPODBONUS_HPP

#include <SaltyEngine/GameObject.hpp>

extern "C"
{
    class SpiralPodBonus : public SaltyEngine::GameObject
    {
    public:
        SpiralPodBonus();
        virtual ~SpiralPodBonus();
    };

    SaltyEngine::Object const *GetObjectPrefab();
};

#endif //RTYPE_SPIRALPODBONUS_HPP
