#pragma once

#ifndef STDMUTEX_HPP
#define STDMUTEX_HPP

#include <mutex>
#include "Thread/BaseMutex.hpp"

class StdMutex : public BaseMutex<std::mutex>
{
public:
	virtual ~StdMutex()
	{};

	explicit StdMutex()
	{};

	virtual void lock();
	virtual void unlock();

	virtual void try_lock();
};

#endif