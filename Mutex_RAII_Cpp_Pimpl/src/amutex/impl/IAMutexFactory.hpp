#pragma once

class IAMutex;

class IAMutexFactory
{
public: 
    virtual std::unique_ptr<IAMutex> create() = 0;
};