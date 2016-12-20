//
// Created by veyrie_f on 20/12/16.
//

#ifndef RTYPE_MATHS_HPP
#define RTYPE_MATHS_HPP

#include <vector>

namespace SaltyEngine
{
    class Mathf
    {

#define VALUE_COUNT 10000
#define INDEXER (VALUE_COUNT / 360.0)

    public:
        static float Cos(float angle);
        static float Sin(float angle);

    private:
        static std::vector<float> m_sin;

        static std::vector<float> m_cos;
    };
}

#endif //RTYPE_MATHS_HPP
