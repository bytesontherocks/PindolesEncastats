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
#include <cstdint>
#include <iostream>
#include <ranges>
#include <stddef.h>

namespace {

    template <typename T>
    auto count_ones(const T x) {
        static_assert(std::is_integral_v<T>, "Error: T must be an integer!");

        size_t           num_of_ones{0};
        constexpr size_t num_of_bits{sizeof(T) * 8};
        auto             bit_shift{0x01};

        for (auto _ : std::views::iota(static_cast<size_t>(0), num_of_bits)) {
            num_of_ones += (x & bit_shift ? 1 : 0);
            bit_shift <<= 1;
        }

        return num_of_ones;
    }

}  // namespace

int main() {

    uint16_t x{0b0011011};
    std::cout << "In binary format the num of ones of ones in: " << x
              << " is: " << count_ones<decltype(x)>(x) << std::endl;

    return 0;
}