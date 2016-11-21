#include "SaltyEngine/Vector3.hpp"

/**
 * @fn	std::ostream & operator<<(std::ostream & os, SaltyEngine::Vector3 & obj)
 *
 * @brief	Stream insertion operator.
 *
 * @param [in,out]	os 	The operating system.
 * @param [in,out]	obj	The object.
 *
 * @return	The shifted result.
 */

std::ostream & operator<<(std::ostream & os, SaltyEngine::Vector3 & obj)
{
	os << "(" << obj.x << ", " << obj.y << ", " << obj.z << ")";
	return (os);
}

/**
 * @fn	SaltyEngine::Vector3 operator*(float val, const SaltyEngine::Vector3 & vec)
 *
 * @brief	Multiplication operator.
 *
 * @param	val	The first value to multiply.
 * @param	vec	The second value to multiply.
 *
 * @return	The result of the operation.
 */

SaltyEngine::Vector3 operator*(float val, const SaltyEngine::Vector3 & vec)
{
	return SaltyEngine::Vector3(vec.x * val, vec.y * val, vec.z * val);
}

/**
 * @fn	SaltyEngine::Vector3 operator*(const SaltyEngine::Vector3 & vec, float val)
 *
 * @brief	Multiplication operator.
 *
 * @param	vec	The first value to multiply.
 * @param	val	The second value to multiply.
 *
 * @return	The result of the operation.
 */

SaltyEngine::Vector3 operator*(const SaltyEngine::Vector3 & vec, float val)
{
	return SaltyEngine::Vector3(vec.x * val, vec.y * val, vec.z * val);
}
