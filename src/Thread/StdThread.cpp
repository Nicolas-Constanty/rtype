#include "Thread/StdThread.hpp"

void StdThread::Stop()
{
}

void StdThread::Join()
{
	_thread->join();
}

void StdThread::Sleep(std::chrono::milliseconds duration)
{
	std::this_thread::sleep_for(duration);
}
