#pragma once

#ifndef ICLONEABLE_HPP_
#define ICLONEABLE_HPP_
#include <memory>
#include <SaltyEngine/Debug.hpp>

template <class T>
class ICloneable
{
public:
	virtual  ~ICloneable() {}
public:
	/**
	 * \brief Shallow copy of the object
	 */
	virtual std::unique_ptr<T> Clone() = 0;
	/**
	 * \brief Deep copy of the object
	 */
	
	template <class U, typename ...Args>
	T *CloneMemberwise(Args... args)
	{
		return dynamic_cast<T *>(new U(args...));
	};
};

#endif