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
		
		static const BaseVector3<T> zero()
		{
			return BaseVector3<T>((T)0, (T)0, (T)0);
		}
	};

	typedef  BaseVector3<double> Vector3d;
	typedef  BaseVector3<float> Vector3f;

	typedef Vector3f Vector3;
}

std::ostream& operator<<(std::ostream& os, SaltyEngine::Vector3& obj);
SaltyEngine::Vector3 operator* (float x, const SaltyEngine::Vector3& y);
SaltyEngine::Vector3 operator* (const SaltyEngine::Vector3& y, float x);

#endif // !VECTOR3_HPP_