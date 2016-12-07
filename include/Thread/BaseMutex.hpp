#pragma once

#ifndef BASEMUTEX_H_
#define BASEMUTEX_H_
#include "Thread/IMutex.hpp"

template <class MutexType>
class BaseMutex : public IMutex
{
public:
	virtual ~BaseMutex() {}

public:
	virtual void lock() {};
	virtual void unlock() {};

	virtual int tryLock() {};

protected:
	BaseMutex()
	{}

protected:
	MutexType m_mutex;
};

#endif