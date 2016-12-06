#pragma once

#ifndef ITHREAD_H_
#define ITHREAD_H_
#include <chrono>

class IThread
{
public:
	virtual ~IThread() {}

public:
	virtual void Stop() = 0;
	virtual void Join() = 0;
	virtual void Sleep(std::chrono::milliseconds) = 0;
};

#endif
