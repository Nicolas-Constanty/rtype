//
// Created by gaspar_q on 12/14/16.
//

#include <Network/Core/Timer.hpp>

Network::Core::Timer::Timer() :
    lastPing(std::chrono::steady_clock::now())
{

}

Network::Core::Timer::Timer(const Network::Core::Timer &ref) :
    lastPing(ref.lastPing)
{

}

Network::Core::Timer::~Timer()
{

}

void Network::Core::Timer::refresh()
{
    lastPing = std::chrono::steady_clock::now();
}

bool Network::Core::Timer::timeout(std::chrono::milliseconds const &limit) const
{
    return std::chrono::steady_clock::now() - lastPing >= limit;
}
