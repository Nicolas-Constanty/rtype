#pragma once

#ifndef IMUTEX_H_
#define IMUTEX_H_
#include <chrono>

class IMutex
{
public:
	virtual ~IMutex() {}

public:

	virtual void lock() = 0;
	virtual void unlock() = 0;

	virtual void try_lock() = 0;
};

#endif
