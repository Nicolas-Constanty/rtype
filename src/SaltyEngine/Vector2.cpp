#include "SaltyEngine/Vector2.hpp"

std::ostream & operator<<(std::ostream & os, SaltyEngine::Vector2 & obj)
{
	os << "(" << obj.x << ", " << obj.y << ")";
	return (os);
}

SaltyEngine::Vector2 operator*(float val, const SaltyEngine::Vector2 & vec)
{
	return SaltyEngine::Vector2(vec.x * val, vec.y * val);
}

SaltyEngine::Vector2 operator*(const SaltyEngine::Vector2 & vec, float val)
{
	return SaltyEngine::Vector2(vec.x * val, vec.y * val);
}
