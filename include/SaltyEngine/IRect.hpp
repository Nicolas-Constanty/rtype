#pragma once

#ifndef IRECT_HPP_
#define IRECT_HPP_

namespace SaltyEngine
{
	template <class T>
	class IRect
	{
	public:
		virtual ~IRect() {};
		virtual bool Contain(const T &vec) const = 0;
		virtual bool Intersect(IRect<T> *) const = 0;
	};
}

#endif // !IRECT_HPP_
