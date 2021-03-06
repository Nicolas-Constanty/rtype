#pragma once

#ifndef ICOLLIDER_HPP_
#define ICOLLIDER_HPP_

#include "SaltyEngine/IRect.hpp"

namespace SaltyEngine
{
	class LIB_EXPORT ICollider
	{
	public:
		virtual void Display(void) = 0;
	};
}

#endif // !ICOLLIDER_HPP_

