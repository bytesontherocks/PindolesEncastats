//MIT License
//
//Copyright (c) [2021] [Guillem Coromina / BytesOnTheRocks]
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:
//
//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


#include "amutex/iface/amutex.hpp"
#include <iostream>
#include <thread>
#include <chrono>


int main ()
{
    std::cout << "This is a sandbox project to play with ideas" << std::endl;

    AMutexFactory amutexfact{};
    auto mtx = AMutex(&amutexfact);

    auto t1 = std::thread ([&]() {
        for(;;)
        {
            {
                std::cout << "Thread 1 tries to get mutex" << std::endl;
                auto l = AMutexGuard(mtx);//it locks the passed in mutex during the life of the object (scope)
                std::cout << "Thread 1 owns mutex for 100ms" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << "Thread 1 releases mutex" << std::endl;
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
	});

    auto t2 = std::thread ([&]() {
        for(;;)
        {
            {
                std::cout << "Thread 2 tries to get mutex" << std::endl;
                auto l = AMutexGuard(mtx);//it locks the passed in mutex during the life of the object (scope)
                std::cout << "Thread 2 owns mutex for 200ms" << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));   
                std::cout << "Thread 2 releases mutex" << std::endl;       
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
	});

    t1.join();
    t2.join();

    return 0;
}