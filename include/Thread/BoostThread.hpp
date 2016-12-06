#pragma once

#ifndef BOOSTTHREAD_H_
#define BOOSTTHREAD_H_

#ifdef _WIN32

#include <thread>
#include <boost/thread/thread.hpp>
#include "Thread/BaseThread.hpp"

class BoostThread : public BaseThread<boost::thread*>
{
public:
	virtual ~BoostThread()
	{
		delete _thread;
	}

	template<class T>
	explicit BoostThread(T func) : BaseThread(new boost::thread(func))
	{
		
	}

	virtual void Stop();
	virtual void Join();
	virtual void Sleep(std::chrono::milliseconds);
};

#endif

#endif