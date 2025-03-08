// MIT License
//
// Copyright (c) [2024] [Guillem Coromina / BytesOnTheRocks]
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

#include "ThreadSafeQueue.hpp"
#include <chrono>
#include <cinttypes>
#include <iostream>
#include <thread>

struct Message {
    uint8_t  fc;
    uint8_t  address;
    uint32_t payload;

    void print() const {
        std::cout << "fc: " << uint32_t(fc) << " address: " << uint32_t(address)
                  << " payload: " << payload << std::endl;
        // std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
};

int main() {
    std::cout << "This is a about queues" << std::endl;

    ThreadSafeQueue<Message> ts_q;

    constexpr std::size_t    TOTAL_NUM_THREADS = 1;  // with 10000 it just slows down massively
    std::vector<std::thread> t_handles;
    bool                     run = true;

    for (std::size_t thread_id = 0; thread_id < TOTAL_NUM_THREADS; ++thread_id) {
        const auto fn = [&](const std::size_t thread_id) {
            uint32_t payload = 100 * thread_id;
            for (;;) {
                if (run) {
                    Message msg{(uint8_t)thread_id, (uint8_t)(thread_id + 33), payload++};
                    ts_q.addItem(std::move(msg));
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                } else {
                    break;
                }
            }
        };
        t_handles.push_back(std::thread(fn, thread_id));
    }

    std::size_t               num_msgs_served = 0;
    std::chrono::microseconds avg_time_consumed_serving_msgs_us{0};

    auto start = std::chrono::high_resolution_clock::now();

    auto t2 = std::thread([&]() {
        // for(;;)
        // {
        //     const auto msg_received = ts_q.getItem();
        //     msg_received.print();
        //     ts_q.removeItem();
        // }

        for (;;) {
            // Method 1: Return a copy but locks the mutex only 1 time
            // auto msg_received = ts_q.copyItem();
            // msg_received.payload++;

            // Method 2: Return a reference (cheaper) but locks the mutex 2 times, to get the item
            // and to remove it
            auto msg_received = ts_q.getItem();
            msg_received.payload++;
            ts_q.removeItem();

            num_msgs_served++;

            auto time_elapsed = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::high_resolution_clock::now() - start);

            if (time_elapsed.count() >= 10) {
                run = false;
                break;
            }

            // msg_received.print();
        }
    });

    for (auto& t : t_handles) {
        t.join();
    }

    t2.join();

    std::cout << "Messages served: " << num_msgs_served << std::endl;

    return 0;
}