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
	virtual std::unique_ptr<T> Clone() = 0;
	virtual std::unique_ptr<T> CloneMemberwise() = 0;
};

#endif