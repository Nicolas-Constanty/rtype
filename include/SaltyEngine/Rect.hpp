#pragma once

#ifndef RECT_HPP_
#define RECT_HPP_

#include "SaltyEngine/Vector2.hpp"
#include "SaltyEngine/IRect.hpp"

namespace SaltyEngine
{
	template <class T>
	class Rect : public IRect<T>
	{
	public:
		Rect(int l, int t, int w, int h) : IRect<T>(), left(l), top(t), width(w), height(h) {};
		~Rect() {};

	public:
		bool Contain(const T &) const override { return false; };
		bool Intersect(IRect<T> * const ) const override { return false; };

	public:
		int left;
		int top;
		int width;
		int height;
	};
}

#endif // !RECT_HPP_

