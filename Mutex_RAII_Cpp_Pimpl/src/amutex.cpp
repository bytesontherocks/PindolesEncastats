#include "amutex.hpp"

void AMutex::lock() { m_pimpl_amutex->lock(); }    
void AMutex::unlock() { m_pimpl_amutex->unlock(); }