#include "SaltyEngine/Vector3.hpp"

std::ostream & operator<<(std::ostream & os, SaltyEngine::Vector3 & obj)
{
	os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
	return (os);
}

SaltyEngine::Vector3 operator*(float val, const SaltyEngine::Vector3 & vec)
{
	return SaltyEngine::Vector3(vec.x * val, vec.y * val, vec.z * val);
}

SaltyEngine::Vector3 operator*(const SaltyEngine::Vector3 & vec, float val)
{
	return SaltyEngine::Vector3(vec.x * val, vec.y * val, vec.z * val);
}
