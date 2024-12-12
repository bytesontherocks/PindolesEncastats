#pragma once

#include "cmsis_os2.h"

class CmsisV2AMutexImpl : public IAMutex
{
public:
    CmsisV2AMutexImpl() {
        mutex_id = osMutexNew(NULL);
    }
    ~CmsisV2AMutexImpl() {
        if (mutex_id != NULL)
            osMutexDelete(mutex_id);
    }  
    // the user is responsible to unlock it
    void lock() { osMutexAcquire(mutex_id, osWaitForever); }    
    void unlock() { osMutexRelease(mutex_id); }

private:
     osMutexId_t mutex_id;  
};

class CmsisV2AMutexImplFactory : public IAMutexFactory
{
public:
    virtual std::unique_ptr<IAMutex> create() {
        return std::make_unique<CmsisV2AMutexImpl>();
    }
};