#include <array>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace {
    int* dangling_ptr() {
        int x = 42;
        return &x;  // Returning address of local variable
    }

}  // namespace
int main(int argc, char** argv) {
    // heap-use-after-free
    // {
    //     auto p = new int[4];
    //     delete[] p;
    //     p[0] = 1;
    // }

    // heap-buffer-overflow
    // {
    //     auto p = new int[4];
    //     p[5]   = 6;
    // }

    // stack-buffer-overflow
    // {
    //     std::array<int, 5> test_array;
    //     test_array[5] = 6;
    // }

    // { *dangling_ptr() = 9; }

    {
        auto sp    = std::make_shared<int>();
        *sp        = 9;
        auto sp_mv = std::move(sp);
        auto i     = *sp;
    }

    return EXIT_FAILURE;
}