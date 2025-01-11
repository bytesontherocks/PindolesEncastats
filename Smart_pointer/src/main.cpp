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

namespace {

    template<typename T>
    class SmartPointer
    {   
      
    public:         
                
        SmartPointer() {
            if (m_ptr == nullptr || m_refCount == nullptr) {
                m_ptr = new T();
                m_refCount = new size_t(1);  
                //(*m_refCount) = 0; // this instance is the first one              
                std::cout << "SmartPointer<> class resource in heap created" << std::endl;
            } 
        }
        T& operator*() { return *m_ptr; }
        T* operator->() { return m_ptr; }        
        SmartPointer<T>& operator=(const SmartPointer<T>& rhs) {
            if (this != &rhs) {
                m_ptr = rhs.m_ptr;
                m_refCount = rhs.m_refCount;
                ++(*m_refCount);
                std::cout << "SmartPointer<> class: copying pointer" << std::endl;
            }
            return *this;   
        };
        ~SmartPointer() {
            if (--(*m_refCount) == 0) {
                delete m_ptr;
                delete m_refCount;
                std::cout << "SmartPointer<> class: resource in heap deleted" << std::endl;
            } else {
                std::cout << "SmartPointer<> class: destructor call but pointer still in use" << std::endl;
            }
        }

    private:      
        //SmartPointer(const SmartPointer<T>&) = delete;
        
        T* m_ptr=nullptr;
        size_t* m_refCount=nullptr;
    };
   
}

int main ()
{
    SmartPointer<uint64_t> sp1{};

    {
        auto p=sp1;
        *p = 5;    
        std::cout << "The value of the pointer p is: " << *p << std::endl;
        *sp1 = 10;
        std::cout << "The value of the pointer sp1 is: " << *sp1 << std::endl;

        std::cout << "Deleting p" << std::endl;
    }

    SmartPointer<uint64_t> sp2{};
    *sp2 = 20;
    sp2 = sp1;
    *sp1 = 15;
    std::cout << "The value of the pointer sp1 is: " << *sp1 << std::endl;
    std::cout << "The value of the pointer sp2 is: " << *sp2 << std::endl;

    std::cout << "End of the program" << std::endl;
    return EXIT_SUCCESS;
}

