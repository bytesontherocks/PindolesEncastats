#include "posix_amutex.hpp"

void PosixAMutexImpl::lock()
{ 
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));// only testing
    mutex_id.lock();
}  

void PosixAMutexImpl::unlock() 
{ 
    mutex_id.unlock(); 
}