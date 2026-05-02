#pragma once

#include <atomic>
#include <stdexcept>
#include <thread>

namespace Work {

    class IWorkItem {
      public:
        virtual ~IWorkItem()   = default;
        virtual void execute() = 0;
    };

    class Worker {
      public:
        Worker() : thread_{[this] { loop(); }} {}

        ~Worker() { stop(); }

        void assign(IWorkItem* wi) {
            if (wi == nullptr) {
                throw std::invalid_argument{"cannot assign a null work item"};
            }

            if (stopping_.load()) {
                throw std::runtime_error{"cannot assign work to a stopping worker"};
            }

            IWorkItem* expected = nullptr;
            if (!work_item_.compare_exchange_strong(expected, wi)) {
                throw std::runtime_error{"worker already has an assigned work item"};
            }

            work_item_.notify_one();
        }

        void stop() {
            const bool was_already_stopping = stopping_.exchange(true);
            thread_.request_stop();

            if (!was_already_stopping) {
                IWorkItem* expected = nullptr;
                work_item_.compare_exchange_strong(expected, &stop_work_item_);
            }

            work_item_.notify_one();
        }

      private:
        class StopWorkItem : public IWorkItem {
          public:
            void execute() override {}
        };

        void loop() {
            while (true) {
                IWorkItem* wi = work_item_.load();

                while (wi == nullptr) {
                    if (stopping_.load()) {
                        return;
                    }

                    work_item_.wait(nullptr);
                    wi = work_item_.load();
                }

                wi = work_item_.exchange(nullptr);

                if (wi == &stop_work_item_) {
                    return;
                }

                wi->execute();

                // notify scheduler that this worker is idle again
            }
        }

        StopWorkItem            stop_work_item_{};
        std::atomic<IWorkItem*> work_item_{nullptr};
        std::atomic_bool        stopping_{false};
        std::jthread            thread_;
    };

}  // namespace Work
