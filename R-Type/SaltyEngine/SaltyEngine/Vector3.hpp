#pragma once

#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

#include <string>
#include <iostream>

namespace SaltyEngine
{
	template<class T>
	class BaseVector3
	{
	public:
		BaseVector3(T _x, T _y, T _z) {
			x = _x;
			y = _y;
			z = _z;
		}
		virtual ~BaseVector3() {};

	public:
		T x;
		T y;
		T z;

		void operator+=(BaseVector3<T> vec)
		{
			x += vec.x;
			y += vec.y;
			z += vec.z;
		}

		template<typename A>
		const BaseVector3<T> &operator+=(A val)
		{
			x *= val;
			y *= val;
			z *= val;
			return (*this)
		}
		
		static const BaseVector3<T> zero()
		{
			return BaseVector3<T>((T)0, (T)0, (T)0);
		}
	};

	typedef  BaseVector3<double> Vector3d;
	typedef  BaseVector3<float> Vector3f;
}

std::ostream& operator<<(std::ostream& os, SaltyEngine::Vector3f& obj);
SaltyEngine::Vector3f operator* (float x, const SaltyEngine::Vector3f& y);
SaltyEngine::Vector3f operator* (const SaltyEngine::Vector3f& y, float x);

#endif // !VECTOR3_HPP_