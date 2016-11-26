#pragma once

#ifndef IRECT_HPP_
#define IRECT_HPP_
#include "SaltyEngine/Vector2.hpp"

namespace SaltyEngine
{
	class IRect
	{
	public:
		virtual ~IRect() {};
		virtual bool Contain(const Vector &vec) const = 0;
	};
}

#endif // !IRECT_HPP_
