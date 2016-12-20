#include "Thread/StdMutex.hpp"

void StdMutex::lock()
{
	m_mutex.lock();
}

void StdMutex::unlock()
{
	m_mutex.unlock();
}

int StdMutex::tryLock()
{
    if (m_mutex.try_lock()) {
        return 1;
    }
    return 0;
}