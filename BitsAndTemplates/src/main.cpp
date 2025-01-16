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
#include <cmath>
#include <limits>
#include <bitset>
#include <array>

// 0       63
// 65472   65535

// x%64
namespace {

void decodeDecimalToBinary(const std::uint32_t d)
{   
    auto t = d;
    std::vector<std::uint32_t> v;
    while(t > 0)
    {
        v.push_back(t % 2);
        t /= 2;
    }

    std::cout << "Binary value: b";
    for(auto it = v.rbegin(); it != v.rend(); ++it)
    {
        std::cout << *it;
    }
    std::cout << std::endl;
}
void decodeDecimalToBinary2(const std::uint32_t d)
{
    const auto num_bits = sizeof(d) * 8;
    static_assert(num_bits <= 32, "Only 32 bits supported");
    std::array<bool, 32> a{0};
    for (std::size_t i = 0; i < num_bits; ++i)
    {
       a[i] = d & (1 << i);
    }
    std::cout << "Binary value: b";
    for(auto it = a.rbegin(); it != a.rend(); ++it)
    {
        std::cout << *it;
    }
    std::cout << std::endl;
}

void decodeDecimalToBinary3(const std::uint32_t d)
{
    std::cout << "Binary value: b" << std::bitset<32>(d).to_string() << std::endl;
}

template <class... Args>
constexpr std::size_t reversed_binary_value(Args... args)
{
    const auto size = sizeof...(args);
    // check if all the arguments are integral types and if there are at least 1 arguments
    if (size == 0 || !(std::is_integral<decltype(args)>::value && ...))
    {
        throw (std::string{"No arguments or not all integers"});
    }

    double result = 0;
    std::size_t exp = 0;
    for(const auto& x : {args...}) {
        std::cout << std::format("x: {}, exp: {}, result: {}", x, exp, result) << std::endl;
		result += x * std::pow(2,exp);
        exp++;       
	}

    
    if (static_cast<double>(std::numeric_limits<size_t>::max()) < result)
    {
        throw (std::string{"Result hold in type double doesn't fit in size_t"});
    }

    return static_cast<std::size_t>(result);
}

}

int main ()
{
    const auto  rv = reversed_binary_value(0, 0, 1);
    std::cout << std::format("Reversed binary value: {}", rv) << std::endl;

    std::uint32_t v{0xF0000000};
    
    decodeDecimalToBinary(v);
    decodeDecimalToBinary2(v);// Whys is not warning about the narrowing type conversion from uint64_t to uint32_t?
    decodeDecimalToBinary3(v);

    // check we catch the exception
    // try
    // {        
    //     reversed_binary_value("a", 0, 1);
    // }
    // catch(const std::string& s)
    // {
    //     std::cerr << s << '\n';
    // }
    
}

