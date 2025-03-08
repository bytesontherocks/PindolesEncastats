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

namespace templates {

    template <class T>
    void printTemplate(const T t) {
        std::cout << "Generic template: " << t << std::endl;
    }

    template <>
    void printTemplate<>(const double t) {
        std::cout << std::format("Specialized template for double types: {:f}", t) << std::endl;
    }

    enum class Mw : std::uint32_t { a = 0, b = 1, c = 2 };

    template <Mw t>
    auto returnDifferentType(const std::string& s);

    template <>
    auto returnDifferentType<Mw::a>(const std::string& s) {
        return std::string{"I'm a!"};
    }

    template <>
    auto returnDifferentType<Mw::b>(const std::string& s) {
        return std::string{"I'm b!"};
    }

    template <>
    auto returnDifferentType<Mw::c>(const std::string& s) {
        return std::string{"I'm c!"};
    }
}  // namespace templates

int main() {
    templates::printTemplate(double{355.0 / 113.0});
    templates::printTemplate(std::uint32_t{98});

    const auto s = templates::returnDifferentType<templates::Mw::b>("not used");
    templates::printTemplate(s);
}
