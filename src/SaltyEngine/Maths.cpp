//
// Created by veyrie_f on 20/12/16.
//

#include <cmath>
#include <algorithm>
#include "SaltyEngine/Maths.hpp"

float SaltyEngine::Mathf::Cos(float angle)
{
    if (angle == 0)
        return 1.0;

    int sign = 1;

    if (angle < 0)
        sign = -1;

    return sign * m_cos[sign * fmodf(angle, 360) * INDEXER - 1];
}

float SaltyEngine::Mathf::Sin(float angle)
{
    if (angle == 0)
        return 0.0;

    int sign = 1;

    if (angle < 0)
        sign = -1;

    return sign * m_sin[sign * fmodf(angle, 360) * INDEXER - 1];

}

std::vector<float> SaltyEngine::Mathf::m_sin = {
#include "SaltyEngine/SFML/sinus.sin"
};

std::vector<float> SaltyEngine::Mathf::m_cos = {
#include "SaltyEngine/SFML/cosinus.cos"
};

float SaltyEngine::Mathf::LerpAngle(float min, float max, float t) {
    t = Clamp01(t);
    if (min > max)
        return min - (min - max) * t;
    return min + (max - min) * t;
}

float SaltyEngine::Mathf::Clamp(float min, float max, float current) {
    return std::min(std::max(current, min), max);
}

float SaltyEngine::Mathf::Clamp01(float value) {
    return Clamp(0, 1, value);
}

float SaltyEngine::Mathf::Sign(float value) {
    return value >= 0 ? 1 : -1;
}
