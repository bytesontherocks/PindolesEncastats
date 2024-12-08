#pragma once

#include <mutex>
#include <chrono>
#include <thread>

class PosixAMutexImpl
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
