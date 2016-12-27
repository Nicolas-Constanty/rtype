//
// Created by veyrie_f on 20/12/16.
//

#ifndef RTYPE_MATHS_HPP
#define RTYPE_MATHS_HPP

#include <vector>
#include <cmath>
#include "Common/DLLexport.hpp"

namespace SaltyEngine
{
    class LIB_EXPORT Mathf
    {

#define VALUE_COUNT 10000
#define INDEXER (VALUE_COUNT / 360.0)

    public:
        static float Cos(float angle);
        static float Sin(float angle);
        static float LerpAngle(float min, float max, float t);
        static float Clamp(float min, float max, float current);
        static float Clamp01(float value);
        static float Sign(float value);

    public:
        constexpr static const float rad2deg = static_cast<float>(180 / M_PI);
        constexpr static const float deg2rad = static_cast<float>(M_PI / 180);

    private:
        static const std::vector<float> m_sin;

        static const std::vector<float> m_cos;
    };
}

#endif //RTYPE_MATHS_HPP
