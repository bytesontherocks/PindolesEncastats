#pragma once

#include <mutex>
#include <chrono>
#include <thread>
#include "../../iface/IAMutexFactory.hpp"
#include <memory>
#include "../../iface/IAMutex.hpp"
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
    std::unique_ptr<IAMutex> create() override {
        return std::make_unique<PosixAMutexImpl>();
    } 
};