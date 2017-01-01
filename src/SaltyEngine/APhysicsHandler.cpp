#include "SaltyEngine/APhysicsHandler.hpp"

namespace SaltyEngine
{
	APhysicsHandler::APhysicsHandler(unsigned int x, unsigned int y) :
		m_size(x, y)
	{

	}

	APhysicsHandler::~APhysicsHandler()
	{

	}

	unsigned int	APhysicsHandler::GetSizeX() const
	{
		return m_size.x;
	}

	unsigned int	APhysicsHandler::GetSizeY() const
	{
		return m_size.y;
	}

	const Vector2ui	&APhysicsHandler::GetSize() const
	{
		return m_size;
	}
}