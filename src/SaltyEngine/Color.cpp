//
// Created by veyrie_f on 24/12/16.
//

#include "SaltyEngine/Color.hpp"

SaltyEngine::Color::Color()
{
}

SaltyEngine::Color::Color(float r, float g, float b, float a) :
        _r(r), _g(g), _b(b), _a(a)
{

}

float SaltyEngine::Color::operator[](int idx) {
    return ((float[]){_r, _g, _b, _a})[idx];
}

float SaltyEngine::Color::r() const {
    return _r;
}

float SaltyEngine::Color::g() const {
    return _g;
}

float SaltyEngine::Color::b() const {
    return _b;
}

float SaltyEngine::Color::a() const {
    return _a;
}

const SaltyEngine::Color &SaltyEngine::Color::GetColor() const {
    return *this;
}

SaltyEngine::Color &SaltyEngine::Color::operator*(float val) {
    _r *= val;
    _g *= val;
    _b *= val;
    _a *= val;
    return *this;
}

SaltyEngine::Color SaltyEngine::Color::White(void) {
    return SaltyEngine::Color(1, 1, 1, 1);
}

SaltyEngine::Color SaltyEngine::Color::Red(void) {
    return SaltyEngine::Color(1, 0, 0, 1);
}

SaltyEngine::Color &SaltyEngine::Color::operator*=(float val) {
    return *this * val;
}
