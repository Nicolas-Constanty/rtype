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

int BoostMutex::tryLock()
{
	return (m_mutex.try_lock());
}

#endif