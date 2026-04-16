// MIT License
//
// Copyright (c) [2025] [Guillem Coromina / BytesOnTheRocks]
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cinttypes>
#include <format>
#include <iostream>
#include <memory>
#include <stdexcept>

// What do we want to do?
// We want to create some object into memory (e.g. heap) and we want to share it among different
// instances of a class. We want to keep track of the number of instances that are using the object
// and we want to delete the object when the last instance is destroyed. We want to avoid the object
// to be deleted if there are still instances using it.
//

namespace {

    template <typename T>
    class SmartPointer {
      public:
        SmartPointer() {
            std::cout << "Creating resources for SmartPointer" << std::endl;
            m_ptr      = new T{};
            m_refCount = new size_t{1};
        }
        ~SmartPointer() {
            if (m_ptr != nullptr && m_refCount != nullptr) {
                --(*m_refCount);
                if (*m_refCount == 0) {
                    delete m_ptr;
                    delete m_refCount;
                }
            }
        };

        SmartPointer(const SmartPointer<T>& rhs) : m_ptr(nullptr), m_refCount(nullptr) {
            if (rhs.m_ptr != nullptr) {
                m_ptr      = rhs.m_ptr;
                m_refCount = rhs.m_refCount;
                ++(*m_refCount);
            }
        }

        SmartPointer(SmartPointer<T>&& rhs) : m_ptr(nullptr), m_refCount(nullptr) {
            m_ptr          = rhs.m_ptr;
            m_refCount     = rhs.m_refCount;
            rhs.m_ptr      = nullptr;
            rhs.m_refCount = nullptr;
        }

        T& operator*() const { return *m_ptr; }

        SmartPointer<T>& operator=(const SmartPointer<T>& rhs) {
            if (rhs.m_ptr != m_ptr) {
                release();
                m_ptr      = rhs.m_ptr;
                m_refCount = rhs.m_refCount;
                if (m_refCount)
                    ++(*m_refCount);
            }
            return *this;
        }

        SmartPointer<T>& operator=(SmartPointer<T>&& rhs) {
            if (rhs.m_ptr != m_ptr) {
                release();
                m_ptr          = rhs.m_ptr;
                m_refCount     = rhs.m_refCount;
                rhs.m_ptr      = nullptr;
                rhs.m_refCount = nullptr;
            }
            return *this;
        }

      private:
        void release() {
            if (m_ptr != nullptr && m_refCount != nullptr) {
                if (--(*m_refCount) == 0) {
                    delete m_ptr;
                    delete m_refCount;
                }
                m_ptr      = nullptr;
                m_refCount = nullptr;

                std::cout << "SmartPointer resources deleted" << std::endl;
            }
        }

        T*      m_ptr{nullptr};
        size_t* m_refCount{nullptr};
    };

}  // namespace

int main() {
    SmartPointer<uint64_t> sp1{};
    *sp1 = 5;
    {
        auto p(sp1);
        *p = 5;
        std::cout << "The value of the pointer p is: " << *p << std::endl;
        std::cout << "The address pointed by the pointer p is: " << &(*p) << std::endl;
        *sp1 = 10;
        std::cout << "The value of the pointer sp1 is: " << *sp1 << std::endl;
        std::cout << "The address pointed by the pointer sp1 is: " << &(*sp1) << std::endl;

        std::cout << "Deleting p" << std::endl;
    }

    std::cout << "Creating sp2" << std::endl;
    SmartPointer<uint64_t> sp2{};
    *sp2 = 20;
    std::cout << "Assigning sp2=sp1" << std::endl;
    sp2  = sp1;
    *sp1 = 15;
    std::cout << "The value of the pointer sp1 is: " << *sp1 << std::endl;
    std::cout << "The address pointed by the pointer sp1 is: " << &(*sp1) << std::endl;
    std::cout << "The value of the pointer sp2 is: " << *sp2 << std::endl;
    std::cout << "The address pointed by the pointer sp2 is: " << &(*sp2) << std::endl;

    const auto sp3 = std::move(sp2);

    std::cout << "The value of the pointer sp3 is: " << *sp3 << std::endl;
    std::cout << "The address pointed by the pointer sp3 is: " << &(*sp3) << std::endl;

    std::cout << "End of the program" << std::endl;
    return EXIT_SUCCESS;
}
