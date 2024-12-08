#include "iface/amutex.hpp"

#include "posix/posix_amutex.hpp"

AMutex::AMutex() : m_pimpl_amutex(std::make_unique<DefaultAMutexImpl>()) {};
AMutex::~AMutex() {}
void AMutex::lock() { m_pimpl_amutex->lock(); }    
void AMutex::unlock() { m_pimpl_amutex->unlock(); }