#pragma once

#ifndef ICLONEABLE_HPP_
#define ICLONEABLE_HPP_
#include <memory>

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
	virtual std::unique_ptr<T> CloneMemberwise() = 0;
};

#endif