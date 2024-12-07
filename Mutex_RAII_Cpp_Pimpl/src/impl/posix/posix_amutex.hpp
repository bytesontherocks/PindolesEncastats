#pragma once

#include <mutex>

class AMutexImpl
{
public:
    void lock() { mutex_id.lock(); }    
    void unlock() { mutex_id.unlock(); }

private:
    std::mutex mutex_id;  
};
