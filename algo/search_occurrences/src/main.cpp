#include <iostream>
#include <map>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    auto num_of_occurrances = 0;

    if (argc > 2) {
        const auto s    = std::string(argv[1]);
        const auto temp = std::string(argv[2]);

        if (temp.length() != 1) {
            std::cout << "incorrect character" << std::endl;
            return EXIT_FAILURE;
        }

        const auto target_char = temp[0];

        std::cout << s << std::endl;

        std::map<char, std::size_t> oc;

        auto cnt = 0U;
        for (const auto& c : s) {
            if (target_char == c) {
                if (++oc[c] > 1) {
                    std::cout << "Second occurrence found in character index: " << cnt << std::endl;
                    return cnt;
                }
            }
            cnt++;
        }
    }

    std::cout << "No second occurrence found. Maybe not even the first occurrence!" << std::endl;

    return EXIT_FAILURE;
}