//
// Created by veyrie_f on 24/12/16.
//

#ifndef RTYPE_COLOR_HPP
#define RTYPE_COLOR_HPP

#include <ostream>

namespace SaltyEngine
{
    class Color
    {
    public:
        Color();
        Color(float r, float g, float b, float a = 1);

        float operator[](int idx);
        float r() const;
        float g() const;
        float b() const;
        float a() const;

        Color const& GetColor() const;

        Color &operator*(float val);
        Color &operator*=(float val);

        static Color White(void);
        static Color Red(void);

    private:
        float _r = 1;
        float _g = 1;
        float _b = 1;
        float _a = 1;

        friend std::ostream &operator<<(std::ostream& stream, Color const& col) {
            stream << "(" << col._r
                   << ", " << col._g
                   << ", " << col._b
                   << ", " << col._a << ")";
            return stream;
        }
    };
}

#endif //RTYPE_COLOR_HPP
