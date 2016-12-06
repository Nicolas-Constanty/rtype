#include "Thread/BoostMutex.hpp"

#ifdef _WIN32

void BoostMutex::lock()
{
	m_mutex.lock();
}

void BoostMutex::unlock()
{
	m_mutex.unlock();
}

void BoostMutex::try_lock()
{
	m_mutex.try_lock();
}

#endif