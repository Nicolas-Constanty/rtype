#include "Vector3.hpp"

std::ostream & operator<<(std::ostream & os, SaltyEngine::Vector3f & obj)
{
	os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
	return (os);
}

SaltyEngine::Vector3f operator*(float val, const SaltyEngine::Vector3f & vec)
{
	return SaltyEngine::Vector3f(vec.x * val, vec.y * val, vec.z * val);
}

SaltyEngine::Vector3f operator*(const SaltyEngine::Vector3f & vec, float val)
{
	return SaltyEngine::Vector3f(vec.x * val, vec.y * val, vec.z * val);
}
