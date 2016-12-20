#include "Thread/BoostThread.hpp"

#ifdef _WIN32

void BoostThread::Stop()
{
	_thread->interrupt();
}

void BoostThread::Join()
{
	_thread->join();
}

void BoostThread::Sleep(std::chrono::milliseconds duration)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

#endif