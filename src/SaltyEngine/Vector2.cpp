#include "SaltyEngine/Vector2.hpp"

/**
 * @fn	std::ostream & operator<<(std::ostream & os, SaltyEngine::Vector2 & obj)
 *
 * @brief	Stream insertion operator.
 *
 * @param [in,out]	os 	The operating system.
 * @param [in,out]	obj	The object.
 *
 * @return	The shifted result.
 */

std::ostream & operator<<(std::ostream & os, SaltyEngine::Vector2 & obj)
{
	os << "(" << obj.x << ", " << obj.y << ")";
	return (os);
}