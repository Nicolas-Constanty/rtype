//
// Created by victor on 06/12/16.
//

#ifndef RTYPE_ITHREADPOOL_HPP
#define RTYPE_ITHREADPOOL_HPP

#include <cstring>

class IThreadPool {
public:
    virtual ~IThreadPool() {}

    virtual void StopThreads() = 0;
    virtual void JoinThreads() = 0;
//    virtual void SleepThread() = 0;
    virtual size_t GetPoolSize() const = 0;
};

#endif //RTYPE_ITHREADPOOL_HPP
