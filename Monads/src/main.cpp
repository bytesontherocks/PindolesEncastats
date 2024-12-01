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
#include <cstdint>
#include <iostream>
#include <format>
#include <vector>
#include <variant>
#include <expected>

//std::cout << std::format("Specialized template for double types: {:f}", t) << std::endl;

namespace {
    std::expected<std::int64_t, std::string> getValue(const bool return_error=false)
    {
        if (false == return_error)
        {
            return 10;           
        }
        return std::unexpected("No value is found");
    }
}

int main ()
{
    const auto l = [](const std::uint32_t val) -> std::expected<std::uint32_t, std::string> {
        std::cout << "Processing value: "<< val << std::endl;

        // a condition that can make this function return an error
        if (false)
        {
            return std::unexpected{"Error: That didn't go well in function 'l'"};
        }

        std::cout << "Initial value found: "<< val << std::endl;
        return val;
    };

    // change integer sign 
    const auto t = [](const std::uint32_t val) -> std::int32_t {        
        return val * -1;
    };

    const auto e = [](const std::string err) -> std::expected<std::int32_t, std::string> {
        std::cout << err << std::endl;
        return std::unexpected{err};
    };

    const auto val = getValue().and_then(l).transform(t).or_else(e);

    if(val.has_value())
    {
        std::cout << "Final value: " << val.value() << std::endl;
    }


    return EXIT_SUCCESS;
}

