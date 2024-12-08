#pragma once

#include "cmsis_os2.h"

class CmsisV2AMutexImpl
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