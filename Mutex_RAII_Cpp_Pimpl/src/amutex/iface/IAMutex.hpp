#pragma once

class IAMutex
{
public:
    virtual void lock() = 0;
    virtual void unlock() = 0;
};