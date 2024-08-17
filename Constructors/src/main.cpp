//MIT License
//
//Copyright (c) [2024] [Guillem Coromina / BytesOnTheRocks]
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
#include <vector>
#include <variant>

namespace {

    class A
    {
        public:
        A() {
            std::cout << "A()" << std::endl;
        };
        A(int in_a, int in_b, int in_c) : a(in_a), b(in_b), c(in_c) {
             std::cout << " A(int in_a, int in_b, int in_c) : a(in_a), b(in_b), c(in_c)" << std::endl;
        };

        ~A() = default;
        A(const A& objA) {
            std::cout << "A(const A& objA)" << std::endl;
            this->b = objA.c;
        };
        A(A&) {
            std::cout << "A(A&)" << std::endl;
        };
        A(A&&) {
            std::cout << "A(A&&)" << std::endl;
        };      

        A& operator=(A& right_a)  {
            std::cout << "A& operator=(A& right_a)" << std::endl;
            this->a = right_a.a;
            this->b = right_a.b;
            this->c = right_a.c;
            return *this;
        }
        void print () const {
            std::cout << a << ", " << b << ", " << c << std::endl;
        }

        int a;
        int b;
        int c;

    };

}

int main ()
{
    auto stackObjA  = A{};

    stackObjA.a = 5;
    stackObjA.b = 6;
    stackObjA.c = 7;
    stackObjA.print();

    // const A anotherA{1, 2, 3};
    // anotherA.print();

    // A a(std::move(A{1, 2, 3}));

    A aa{};
    aa = stackObjA;

    aa.print();
   
    return 0;
}

