#include <boost/signals2.hpp>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_set>
#include <vector>

namespace {

    class ScopedCoutCapture {
      public:
        ScopedCoutCapture() : old_buffer_{std::cout.rdbuf(stream_.rdbuf())} {}

        ~ScopedCoutCapture() { std::cout.rdbuf(old_buffer_); }

        ScopedCoutCapture(const ScopedCoutCapture&)            = delete;
        ScopedCoutCapture& operator=(const ScopedCoutCapture&) = delete;

        std::string Release() {
            std::cout.rdbuf(old_buffer_);
            old_buffer_ = nullptr;
            return stream_.str();
        }

      private:
        std::ostringstream stream_{};
        std::streambuf*    old_buffer_{};
    };

    auto ParseHandledMessages(const std::string& output) {
        constexpr auto kPrefix = std::string_view{"Processing: "};

        auto handled_messages = std::unordered_set<std::string>{};
        auto stream           = std::istringstream{output};
        auto line             = std::string{};
        while (std::getline(stream, line)) {
            if (line.rfind(kPrefix, 0) == 0) {
                handled_messages.insert(line.substr(kPrefix.size()));
            }
        }
        return handled_messages;
    }

    class Observer {
      public:
        enum class StopMode {
            kRunning,
            kDrain,
            kStopNow,
        };

        void OnEvent(const std::string& msg) {
            auto lg = std::lock_guard{mtx_};
            if (stop_mode_ != StopMode::kRunning) {
                return;
            }
            queue_.push(msg);
            cv_.notify_one();
        }

        void StopNow() {
            auto lg    = std::lock_guard{mtx_};
            stop_mode_ = StopMode::kStopNow;
            std::queue<std::string> empty{};
            queue_.swap(empty);
            cv_.notify_all();
        }

        void StopAfterDrain() {
            auto lg = std::lock_guard{mtx_};
            if (stop_mode_ == StopMode::kRunning) {
                stop_mode_ = StopMode::kDrain;
            }
            cv_.notify_all();
        }

        void Worker(std::stop_token st) {
            std::stop_callback on_stop{st, [this]() { cv_.notify_all(); }};

            while (true) {
                std::string msg;

                {
                    auto ul = std::unique_lock{mtx_};
                    cv_.wait(ul, [this, &st]() {
                        return st.stop_requested() || stop_mode_ != StopMode::kRunning ||
                               !queue_.empty();
                    });

                    if (stop_mode_ == StopMode::kStopNow) {
                        break;
                    }

                    if (!queue_.empty()) {
                        msg = queue_.front();
                        queue_.pop();
                    } else if (stop_mode_ == StopMode::kDrain || st.stop_requested()) {
                        break;
                    }
                }

                std::cout << "Processing: " << msg << '\n';
            }

            std::cout << "Worker stopping\n";
        }

      private:
        std::mutex                  mtx_{};
        std::condition_variable_any cv_{};
        std::queue<std::string>     queue_{};
        StopMode                    stop_mode_{StopMode::kRunning};
    };
}  // namespace

int main() {
    auto capture = ScopedCoutCapture{};

    // Boost.Signals2 gives us a thread-safe publish/subscribe point:
    // producers emit a string event through `signal(...)`, and the connected slot
    // forwards each message into the observer-owned queue.
    boost::signals2::signal<void(const std::string&)> signal;

    auto obs = Observer{};

    auto c = signal.connect([&obs](const std::string& msg) { obs.OnEvent(msg); });
    static_cast<void>(c);

    std::jthread event_handler([&obs](std::stop_token st) { obs.Worker(st); });

    // Stress test: hundreds of producer threads emit distinct messages concurrently.
    // After all producers finish, the observer switches to drain mode and the test
    // verifies from the worker output that every expected message was processed.
    constexpr std::size_t producer_count        = 200;
    constexpr std::size_t messages_per_producer = 10;

    auto expected_messages = std::vector<std::string>{};
    expected_messages.reserve(producer_count * messages_per_producer);

    auto producers = std::vector<std::thread>{};
    producers.reserve(producer_count);

    for (auto producer = 0U; producer < producer_count; ++producer) {
        for (auto message = 0U; message < messages_per_producer; ++message) {
            expected_messages.push_back("producer_" + std::to_string(producer) + "_message_" +
                                        std::to_string(message));
        }
    }

    for (auto producer = 0U; producer < producer_count; ++producer) {
        producers.emplace_back([producer, messages_per_producer, &signal]() {
            for (auto message = 0U; message < messages_per_producer; ++message) {
                signal("producer_" + std::to_string(producer) + "_message_" +
                       std::to_string(message));
            }
        });
    }

    for (auto& producer : producers) {
        producer.join();
    }

    obs.StopAfterDrain();
    event_handler.request_stop();
    event_handler.join();

    const auto captured_output  = capture.Release();
    const auto handled_messages = ParseHandledMessages(captured_output);

    auto all_handled = handled_messages.size() == expected_messages.size();
    if (all_handled) {
        for (const auto& msg : expected_messages) {
            if (!handled_messages.contains(msg)) {
                all_handled = false;
                break;
            }
        }
    }

    std::cout << "Handled " << handled_messages.size() << " of " << expected_messages.size()
              << " expected messages\n";
    std::cout << "All messages handled: " << std::boolalpha << all_handled << '\n';

    return all_handled ? 0 : 1;
}
