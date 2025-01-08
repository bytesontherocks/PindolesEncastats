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

//std::cout << std::format("Specialized template for double types: {:f}", t) << std::endl;

namespace {

    struct Message1{};
    struct Message2{};
    struct Message3{};
    struct Message4{};
    struct Message5{};
    
    using Message = std::variant<Message1, Message2, Message3, Message4>;

    // std::visit approach
    struct ProcessMessage {
        void operator()(const Message1 msg1) const {
            std::cout << "Processing Message 1!" << std::endl;
        }
        void operator()(const Message2 msg2) const {
            std::cout << "Processing Message 2!" << std::endl;
        }
        void operator()(const Message3 msg3) const {
            std::cout << "Processing Message 3!" << std::endl;
        }
        void operator()(const Message4 msg4) const { // Compilation error if type is not handled (e.g. adding new type but is forgotten to be handled)
            std::cout << "Processing Message 4!" << std::endl;
        }
    };

    using Messages = std::vector<Message>;

    // std::get_if<> approach
    void processMessage(Messages const& msgs)
    {
        for (auto const& msg : msgs) {

            if (const Message1* msg1 = std::get_if<Message1>(&msg))
                std::cout << "Processing Message 1!" << std::endl;
            if (const Message2* msg2 = std::get_if<Message2>(&msg))
                std::cout << "Processing Message 2!" << std::endl;
            if (const Message3* msg3 = std::get_if<Message3>(&msg))
                 std::cout << "Processing Message 3!" << std::endl;
            if (const Message4* msg4 = std::get_if<Message4>(&msg)) // No compilation error if type is not handled (e.g. adding new type but is forgotten to be handled)
                std::cout << "Processing Message 4!" << std::endl;

            // Compilation error if the object type is not in the variant
            //
            // if (const Message5* msg5 = std::get_if<Message5>(&msg))
            //     std::cout << "Processing Message 5!" << std::endl;
        }
    }
}

int main ()
{
    const std::vector<Message> vv{Message2{}, Message1{}, Message4{}, Message3{}, Message2{}};

    {
        // solution using std::visit
        //     
        std::cout << "Solution using std::variant: " << std::endl;
        for (const auto& msg : vv)
            std::visit(ProcessMessage{}, msg);
    }

    {
        // solution using std::get_if (higher performance)
        //
        std::cout << "Solution using std::get_if<>: " << std::endl;
        processMessage(vv);

    }
   
}

