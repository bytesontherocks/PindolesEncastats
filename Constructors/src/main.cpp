// MIT License
//
// Copyright (c) [2024] [Guillem Coromina / BytesOnTheRocks]
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
#include <variant>
#include <vector>

namespace {

    class A {
      public:
        A() { std::cout << "default constructor A()" << std::endl; };
        A(int in_a, int in_b, int in_c) : a(in_a), b(in_b), c(in_c) {
            std::cout << " A(int in_a, int in_b, int in_c) : a(in_a), b(in_b), c(in_c)"
                      << std::endl;
        };

        ~A() = default;
        A(const A& objA) {
            std::cout << "const ref A(const A&)" << std::endl;
            this->b = objA.c;
        };
        A(A&) { std::cout << "non-const ref constructor A(A&)" << std::endl; };
        A(A&&) { std::cout << "A(A&&)" << std::endl; };

        A& operator=(const A& right_a) {
            std::cout << "A& operator=(const A&)" << std::endl;
            this->a = right_a.a;
            this->b = right_a.b;
            this->c = right_a.c;
            return *this;
        }
        A& operator=(A&& right_a) {
            if (this != &right_a) {  // Prevent self-assignment
                std::cout << "A& operator=(A&&)" << std::endl;
                this->a = right_a.a;
                this->b = right_a.b;
                this->c = right_a.c;
            }
            return *this;
        }

        // ref and const qualifiers
        void show() & { std::cout << "Lvalue, non-const\n"; }
        void show() const& { std::cout << "Lvalue, const\n"; }
        void show() && { std::cout << "Rvalue, non-const\n"; }
        void show() const&& { std::cout << "Rvalue, const\n"; }

      private:
        int32_t a, b, c;
    };

}  // namespace

int main() {
    auto       non_constA = A{};
    const auto constA{A{1, 2, 3}};
    auto       non_constA_copy{non_constA};
    auto       constA_copy{constA};
    auto       non_constA_moved{std::move(non_constA)};
    auto       constA_moved{std::move(constA)};  // uses  A(const A& objA)
    non_constA.show();
    constA.show();
    A{}.show();
    std::move(constA).show();

    return 0;
}
