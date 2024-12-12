#pragma once 

#ifndef CMSIS_V2
//class PosixAMutexImpl;
//class PosixAMutexImpl;
#include "impl/posix/posix_amutex.hpp"
using DefaultAMutexImpl = PosixAMutexImpl;
using DefaultAMutexImplFactory = PosixAMutexImplFactory;
#else
// class CmsisV2AMutexImpl;
// using DefaultAMutexImpl = CmsisV2AMutexImpl;
using DefaultAMutexImplFactory =CmsisV2ImplFactory;
#endif