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
		BaseVector2() {
			x = (T)0;
			y = (T)0;
		}
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

	;
	typedef  BaseVector2<float> Vector2f;
	typedef  BaseVector2<int> Vector2fi;
	typedef  BaseVector2<double> Vector2d;

#ifndef GAME2D
	typedef Vector2f Vector2, Vector;
#else
	typedef Vector2f Vector2;
#endif
}

std::ostream& operator<<(std::ostream& os, SaltyEngine::Vector2& obj);


/**
* @fn	SaltyEngine::Vector2 operator*(float val, T & vec)
*
* @brief	Multiplication operator.
* @param 		  	val	The first value to multiply.
* @param [in,out]	vec	The second value to multiply.
*
* @return	The result of the operation.
*/
template<class T>
SaltyEngine::Vector2 operator*(float val, T & vec)
{
	return SaltyEngine::Vector2(vec.x * val, vec.y * val);
}

/**
* @fn	SaltyEngine::Vector2 operator*(const SaltyEngine::Vector2 & vec, T val)
*
* @brief	Multiplication operator.
*
* @param	vec	The first value to multiply.
* @param	val	The second value to multiply.
*
* @return	The result of the operation.
*/
template<class T>
SaltyEngine::Vector2 operator*(const SaltyEngine::Vector2 & vec, T val)
{
	return SaltyEngine::Vector2(vec.x * val, vec.y * val);
}

#endif // !VECTOR2_HPP_