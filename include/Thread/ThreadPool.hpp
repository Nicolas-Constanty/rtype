//
// Created by victor on 06/12/16.
//

#ifndef RTYPE_BASICTHREADPOOL_HPP
#define RTYPE_BASICTHREADPOOL_HPP

#include <memory>
#include <vector>
#include "IThreadPool.hpp"
#include "IThread.hpp"

template <typename ThreadType>
class ThreadPool : public IThreadPool {
public:
    ThreadPool() {}
    virtual ~ThreadPool() {}

public:
    template <class Func, class ... Args>
    void AddThread(Func func, Args &&... args) {
        pools.emplace_back(new ThreadType(func, args...));
    }

    virtual void StopThreads() {
        for (std::unique_ptr<ThreadType> &thread : pools) {
            thread->Stop();
        }
    }

    virtual void JoinThreads() {
        for (std::unique_ptr<ThreadType> &thread : pools) {
            thread->Join();
        }
    }

    virtual size_t GetPoolSize() const {
        return (pools.size());
    }

private:
    std::vector<std::unique_ptr<ThreadType> >  pools;
};

#endif //RTYPE_BASICTHREADPOOL_HPP
