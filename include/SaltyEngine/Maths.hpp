//
// Created by veyrie_f on 20/12/16.
//

#ifndef RTYPE_MATHS_HPP
#define RTYPE_MATHS_HPP

#include <vector>
#include <cmath>

namespace SaltyEngine
{
    class Mathf
    {

#define VALUE_COUNT 10000
#define INDEXER (VALUE_COUNT / 360.0)

    public:
        static float Cos(float angle);
        static float Sin(float angle);

    public:
        constexpr static const float rad2deg = (180 / M_PI);
        constexpr static const float deg2rad = (M_PI / 180);

    private:
        static std::vector<float> m_sin;

        static std::vector<float> m_cos;
    };
}

#endif //RTYPE_MATHS_HPP
