//MIT License
//
//Copyright (c) [2021] [Guillem Coromina / BytesOnTheRocks]
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

#pragma once

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

#ifdef MUTEX_CPP11

#include <mutex>

class Mutex
{
public:
    // the user is responsible to unlock it
    void lock() { mutex_id.lock(); }    
    void unlock() { mutex_id.unlock(); }

private:
    std::mutex mutex_id;  
};

#endif

class MutexGuard
{
public:
    explicit MutexGuard(Mutex& mutex) : mMutex{mutex} {
        mMutex.lock();
    }
    ~MutexGuard() {
        mMutex.unlock();
    }

private:
    Mutex& mMutex;
};