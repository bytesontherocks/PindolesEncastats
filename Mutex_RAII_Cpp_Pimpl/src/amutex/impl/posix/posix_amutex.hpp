#pragma once

#include <mutex>
#include <chrono>
#include <thread>
#include "../../iface/IAMutexFactory.hpp"
#include <memory>
#include "../../iface/IAMutex.hpp"

class PosixAMutexImpl final : public IAMutex
{
public:
    void lock() override; 
    void unlock() override;

private:
    std::mutex mutex_id;  
};

class PosixAMutexImplFactory final : public IAMutexFactory
{
public:
    std::unique_ptr<IAMutex> create() override {
        return std::make_unique<PosixAMutexImpl>();
    } 
};