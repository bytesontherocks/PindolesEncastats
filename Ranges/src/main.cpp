#include <iostream>
#include <ranges>
#include <vector>

int main() {
    {
        // piping outputs
        //
        std::vector<int> ints{0, 1, 2, 3, 4, 5};
        auto             even   = [](int i) { return 0 == i % 2; };
        auto             square = [](int i) { return i * i; };

        for (int i : ints | std::views::filter(even) | std::views::transform(square)) {
            std::cout << i << ' ';
        }
    }

    {
        // braking down the solution
        //
        std::vector<int> ints{0, 1, 2, 3, 4, 5};
        auto             even   = [](int i) { return 0 == i % 2; };
        auto             square = [](int i) { return i * i; };

        auto ve = std::views::filter(ints, even);

        std::cout << std::endl;

        for (const auto& e : ve) {
            std::cout << e << ' ';
        }

        auto sq = std::views::transform(ve, square);

        std::cout << std::endl;

        for (const auto& s : sq) {
            std::cout << s << ' ';
        }
    }
}