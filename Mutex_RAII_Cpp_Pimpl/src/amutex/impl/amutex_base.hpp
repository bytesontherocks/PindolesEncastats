#pragma once 
#include "IAMutexFactory.hpp"
#include "IAMutex.hpp"
#include <memory>

class AMutexBase
{
public:
    AMutexBase(IAMutexFactory* amutex_factory) {
        m_impl = amutex_factory->create();
    };
    auto& getImpl() const {return m_impl;};

private:
   std::unique_ptr<IAMutex> m_impl{};
};