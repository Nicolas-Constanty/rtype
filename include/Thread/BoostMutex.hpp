#pragma once

#ifndef BOOSTMUTEX_H_
#define BOOSTMUTEX_H_

#ifdef _WIN32

#include <boost/thread/mutex.hpp>
#include "Thread/BaseMutex.hpp"

class BoostMutex : public BaseMutex<boost::mutex>
{
public:
	virtual ~BoostMutex()
	{};

	explicit BoostMutex()
	{};
	
	virtual void lock();
	virtual void unlock();

	virtual int tryLock();
};

#endif

#endif