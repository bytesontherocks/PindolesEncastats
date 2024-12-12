#pragma once 
#include "IAMutexFactory.hpp"
#include "IAMutex.hpp"
#include <memory>
#include "amutex_pimpl.hpp"

class AMutexBase
{
public:
    AMutexBase(IAMutexFactory* amutex_factory) {
        if (nullptr == amutex_factory) {
            DefaultAMutexImplFactory impl_factory{};
            m_impl = impl_factory.create();
        } else {
            m_impl = amutex_factory->create();
        }
    };
    auto& getImpl() const {return m_impl;};

private:
   std::unique_ptr<IAMutex> m_impl{};
};