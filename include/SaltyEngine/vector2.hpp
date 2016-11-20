#pragma once

#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_

#include <string>
#include <iostream>

namespace SaltyEngine
{
	template<class T>
	class BaseVector2
	{
	public:
		BaseVector2(T _x, T _y) {
			x = _x;
			y = _y;
		}
		virtual ~BaseVector2() {};

	public:
		T x;
		T y;

		void operator+=(BaseVector2<T> vec)
		{
			x += vec.x;
			y += vec.y;
		}

		static const BaseVector2<T> zero()
		{
			return BaseVector2<T>((T)0, (T)0);
		}
	};

	typedef  BaseVector2<double> Vector2d;
	typedef  BaseVector2<float> Vector2f;
	typedef  BaseVector2<int> Vector2fi;

	typedef Vector2f Vector2;
}

std::ostream& operator<<(std::ostream& os, SaltyEngine::Vector2& obj);
SaltyEngine::Vector2 operator* (float x, const SaltyEngine::Vector2& y);
SaltyEngine::Vector2 operator* (const SaltyEngine::Vector2& y, float x);

#endif // !VECTOR2_HPP_