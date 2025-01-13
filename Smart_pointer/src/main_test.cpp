//MIT License
//
//Copyright (c) [2025] [Guillem Coromina / BytesOnTheRocks]
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

#include <cinttypes>
#include <iostream>
#include <format>
#include <stdexcept>
#include <memory>


namespace {

 
   struct A
    {
        A(int a) : m_a(a){
            std::cout << "A constructorA val: " << m_a << std::endl;
        }
        ~A() {
            std::cout << "A destructor A val: " << m_a << std::endl;
        }

        friend std::ostream& operator<<(std::ostream& os, const A& rhs)
        {
            return os << rhs.m_a;
        }
                    
        int m_a;
    };
}

int main ()
{
    {
        // quick test to see what happens when 2 shared_ptrs are pointing different objects but you copy one over the other. Is the resource pointed by the overwritten one left 
        // leaking?
        auto s1 = std::make_shared<A>(12);

        std::cout << *s1 << std::endl; // 12

        auto s2 =  std::make_shared<A>(66);
        
        std::cout << "val s1: " << *s1 << " address pointer at by s1: " << &(*s1) << std::endl; 
        std::cout << "val s2: " << *s2 << " address pointer at by s2: " << &(*s2) << std::endl; 
        
        std::cout << "s2 copied with content with content with s1... what happens with s2 allocated resources. e.g. T* and ref_counter ?" << std::endl;
        
        s2 = s1; // The destructor of the s2 resources is done as part of the process of copying s1
        
        std::cout << "val s1: " << *s1 << " address pointer at by s1: " << &(*s1) << std::endl; 
        std::cout << "val s2: " << *s2 << " address pointer at by s2: " << &(*s2) << std::endl; 
        
        std::cout << "sp2 out of scope" << std::endl;
    }

    std::cout << "End of the program" << std::endl;
    return EXIT_SUCCESS;
}

