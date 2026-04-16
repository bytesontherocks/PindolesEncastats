#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <expected>
#include <iostream>
#include <ranges>
#include <source_location>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace {
    class ScopedTimer {
      public:
        using ClockType = std::chrono::steady_clock;
        ScopedTimer(const char* func) : function_name_{func}, start_{ClockType::now()} {}
        ScopedTimer(const ScopedTimer&)                    = delete;
        ScopedTimer(ScopedTimer&&)                         = delete;
        auto operator=(const ScopedTimer&) -> ScopedTimer& = delete;
        auto operator=(ScopedTimer&&) -> ScopedTimer&      = delete;
        ~ScopedTimer() {
            using namespace std::chrono;
            auto stop     = ClockType::now();
            auto duration = (stop - start_);
            auto ms       = duration_cast<milliseconds>(duration).count();
            std::cout << ms << " ms " << function_name_ << '\n';
        }

      private:
        const char*                 function_name_{};
        const ClockType::time_point start_{};
    };

    void functionToMeasure(int& todo) {
        const auto loc = std::source_location::current();
        const auto t   = ScopedTimer(loc.function_name());
        todo++;
    };

}  // namespace

///
int main() {
    auto i = 0;
    functionToMeasure(i);
}