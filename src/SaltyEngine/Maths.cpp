//
// Created by veyrie_f on 20/12/16.
//

#include "SaltyEngine/Maths.hpp"

float SaltyEngine::Mathf::Cos(float angle)
{
    if (angle == 0)
        return 1.0;

    int sign = 1;

    if (angle < 0)
        sign = -1;

    angle *= INDEXER;
    return sign * m_cos[sign * angle - 1];
}

float SaltyEngine::Mathf::Sin(float angle)
{
    if (angle == 0)
        return 0.0;

    int sign = 1;

    if (angle < 0)
        sign = -1;

    angle *= INDEXER;
    return sign * m_sin[sign * angle - 1];
}

std::vector<float> SaltyEngine::Mathf::m_sin = {
#include "SaltyEngine/SFML/sinus.sin"
};

std::vector<float> SaltyEngine::Mathf::m_cos = {
#include "SaltyEngine/SFML/cosinus.cos"
};