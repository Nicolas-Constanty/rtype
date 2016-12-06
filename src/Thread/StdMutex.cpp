#include "Thread/StdMutex.hpp"

void StdMutex::lock()
{
	m_mutex.lock();
}

void StdMutex::unlock()
{
	m_mutex.unlock();
}

void StdMutex::try_lock()
{
	m_mutex.try_lock();
}