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

using DefaultAMutexImpl = AMutexImpl;


//#define CMSIS_V2
#define MUTEX_CPP11

#ifdef CMSIS_V2

#include "cmsis_os2.h"

//allow declaring a "self-destroying" object acording to the scope to avoid risk to keep mutex acquired

class Mutex
{
public:
    Mutex() {
        mutex_id = osMutexNew(NULL);
    }
    ~Mutex() {
        if (mutex_id != NULL)
            osMutexDelete(mutex_id);
    }  
    // the user is responsible to unlock it
    void lock() { osMutexAcquire(mutex_id, osWaitForever); }    
    void unlock() { osMutexRelease(mutex_id); }

private:
    osMutexId_t mutex_id;  
};

#endif