#pragma once

class IAMutex {
  public:
    virtual ~IAMutex()    = default;
    virtual void lock()   = 0;
    virtual void unlock() = 0;
};