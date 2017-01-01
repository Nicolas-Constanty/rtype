#ifndef A_PHYSICS_HANDLER_HPP
#define A_PHYSICS_HANDLER_HPP

#include "IPhysicHandler.hpp"
#include "Vector2.hpp"

namespace SaltyEngine
{
	class LIB_EXPORT APhysicsHandler : public IPhysicsHandler
	{
	public:
		APhysicsHandler(unsigned int x, unsigned int y);
		virtual ~APhysicsHandler();

		unsigned int GetSizeX() const;

		unsigned int GetSizeY() const;

		const Vector2ui &GetSize() const;

		virtual void Clear() = 0;
		virtual void Update() = 0;
		virtual void Run() = 0;
		virtual void Display() = 0;
		virtual void Collide() = 0;

	protected:
		Vector2ui m_size;
	};
}

#endif // !A_PHYSICS_HANDLER_HPP
