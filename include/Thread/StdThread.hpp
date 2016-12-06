#pragma once

#ifndef STDTHREAD_H_
#define STDTHREAD_H_

#include <thread>
#include "Thread/BaseThread.hpp"

class StdThread : public BaseThread<std::thread *>
{
public:
	template<class Func, class ... Args>
	explicit StdThread(Func func, Args &&... args) : BaseThread(new std::thread(func, args...))
	{}
	virtual ~StdThread()
	{
		delete _thread;
	}

public:
	virtual void Stop();
	virtual void Join();
	virtual void Sleep(std::chrono::milliseconds);
};

#endif