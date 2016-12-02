#pragma once

#ifndef ICOLLIDER_HPP_
#define ICOLLIDER_HPP_

#include "SaltyEngine/IRect.hpp"

namespace SaltyEngine
{
	class ICollider
	{
	public:
		virtual void Display(void) = 0;
		//virtual IRect<T> *GetBound(void) const = 0;
	};
}

#endif // !ICOLLIDER_HPP_

