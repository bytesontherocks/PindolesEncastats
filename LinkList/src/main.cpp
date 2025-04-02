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

#include <chrono>
#include <cinttypes>
#include <iostream>
#include <memory>
#include <ranges>
#include <thread>
#include <vector>

namespace {

    template <typename T>
    class Node {
      public:
        explicit Node(const T& val) : val(std::move(val)) {}
        std::shared_ptr<Node<T>> next{nullptr};
        T                        val;
    };

    template <typename T>
    class LinkedList {
      public:
        void push_back(std::shared_ptr<Node<T>> node_to_push) {
            if (!m_head) {
                std::cout << "list has been initialised - head has been set" << std::endl;
                m_head = std::move(node_to_push);
                m_tail = m_head;
                return;
            }

            {
                // using tail
                auto& node_next{m_tail->next};
                node_next = std::move(node_to_push);
                m_tail    = node_next;
            }
        };

        void push_front(std::shared_ptr<Node<T>> node_to_push) {
            if (!m_head) {
                std::cout << "list has been initialised - head has been set" << std::endl;
                m_head = std::move(node_to_push);
                m_tail = m_head;
                return;
            }

            {
                node_to_push->next = m_head;
                m_head             = std::move(node_to_push);
            }
        };

        bool isEmpty() const { return !m_head; };

        void printElements() {
            auto next{m_head};
            while (nullptr != next) {
                std::cout << "node with val: " << next->val << std::endl;
                next = next->next;
            };

            std::cout << "head ref counts: " << m_head.use_count() << std::endl;
            std::cout << "tail ref counts: " << m_tail.use_count() << std::endl;
        }

        T find(){};

      private:
        std::shared_ptr<Node<T>> m_head{nullptr};
        std::shared_ptr<Node<T>> m_tail{nullptr};
    };

    template <typename T>
    auto createNodeSharedPointer(const T val) {
        return std::make_shared<Node<T>>(val);
    }
}  // namespace

int main() {
    std::cout << "This is a about link lists" << std::endl;

    LinkedList<std::uint32_t> ll{};

    for (int i : std::views::iota(0, 5)) {
        ll.push_back(std::move(createNodeSharedPointer<std::uint32_t>(42 + i)));
        // ll.push_front(std::move(createNodeSharedPointer<std::uint32_t>(12 + i)));
    }

    ll.printElements();

    // constexpr std::size_t    TOTAL_NUM_THREADS = 1;  // with 10000 it just slows down massively
    // std::vector<std::thread> t_handles;
    // bool                     run = true;

    // for (std::size_t thread_id = 0; thread_id < TOTAL_NUM_THREADS; ++thread_id) {
    //     const auto fn = [&](const std::size_t thread_id) {
    //         uint32_t payload = 100 * thread_id;
    //         for (;;) {
    //             if (run) {
    //                 std::this_thread::sleep_for(std::chrono::milliseconds(1));
    //             } else {
    //                 break;
    //             }
    //         }
    //     };
    //     t_handles.push_back(std::thread(fn, thread_id));
    // }

    // std::size_t               num_msgs_served = 0;
    // std::chrono::microseconds avg_time_consumed_serving_msgs_us{0};

    // auto start = std::chrono::high_resolution_clock::now();

    // auto t2 = std::thread([&]() {
    //     for (;;) {
    //         num_msgs_served++;

    //         auto time_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
    //             std::chrono::high_resolution_clock::now() - start);

    //         if (time_elapsed.count() >= 10) {
    //             run = false;
    //             break;
    //         }
    //     }
    // });

    // for (auto& t : t_handles) {
    //     t.join();
    // }

    // t2.join();

    // std::cout << "Messages served: " << num_msgs_served << std::endl;

    return 0;
}