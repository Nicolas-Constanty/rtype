#pragma once

#ifndef BASETHREAD_H_
#define BASETHREAD_H_
#include "Thread/IThread.hpp"

template <class ThreadType>
class BaseThread : public IThread
{
public:
	virtual ~BaseThread() {}

public:
	virtual void Stop() {}
	virtual void Join() {}
	virtual void Sleep(std::chrono::milliseconds) {}

protected:
	BaseThread(ThreadType thread) :
		_thread(thread)
	{}

protected:
	ThreadType _thread;
};

#endif