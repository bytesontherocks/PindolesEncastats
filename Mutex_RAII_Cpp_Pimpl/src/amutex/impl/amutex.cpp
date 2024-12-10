#include "iface/amutex.hpp"

#include "posix/posix_amutex.hpp"

AMutex::~AMutex() {}
void AMutex::lock() { getImpl()->lock(); }    
void AMutex::unlock() { getImpl()->unlock(); }