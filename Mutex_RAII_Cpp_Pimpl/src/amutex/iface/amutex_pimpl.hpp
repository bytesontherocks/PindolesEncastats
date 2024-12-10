#pragma once 

#ifndef CMSIS_V2
//class PosixAMutexImpl;
#include "impl/posix/posix_amutex.hpp"
using DefaultAMutexImpl = PosixAMutexImpl;
#else
// class CmsisV2AMutexImpl;
// using DefaultAMutexImpl = CmsisV2AMutexImpl;
#endif