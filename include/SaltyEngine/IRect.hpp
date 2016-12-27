#pragma once

#ifndef IRECT_HPP_
#define IRECT_HPP_

#include "Common/DLLexport.hpp"

namespace SaltyEngine
{
	template <class T>
	class LIB_EXPORT IRect
	{
	public:
		virtual ~IRect() {};
		virtual bool Contain(const T &vec) const = 0;
		virtual bool Intersect(IRect<T> * const) const = 0;
	};
}

#endif // !IRECT_HPP_
