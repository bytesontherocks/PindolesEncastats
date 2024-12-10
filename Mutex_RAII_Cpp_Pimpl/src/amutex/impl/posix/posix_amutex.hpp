#pragma once

#include <mutex>
#include <chrono>
#include <thread>
#include "../IAMutexFactory.hpp"
#include <memory>
#include "../IAMutex.hpp"
class PosixAMutexImpl : public IAMutex
{
public:
    void lock() { 
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        mutex_id.lock();
    }    
    void unlock() { mutex_id.unlock(); }

private:
    std::mutex mutex_id;  
};

class PosixAMutexImplFactory : public IAMutexFactory
{
public:
    virtual std::unique_ptr<IAMutex> create() {
        return std::make_unique<PosixAMutexImplFactory>();
    }
};