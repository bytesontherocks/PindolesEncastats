#include "worker.h"
#include <array>
#include <iostream>
#include <optional>
#include <queue>

namespace {

    using namespace Work;

    class Scheduler {
      public:
        Scheduler() {
            for (int i = 0; i < NUM_MAX_WORKERS; ++i) {
                idle_workers_.emplace(&workers_[i]);
            }
        }

        ~Scheduler() {
            for (auto& w : workers_) {
                w.stop();
            }
        }

        bool assign_job(IWorkItem* wi) {
            auto maybe_t = getIdleWorker();

            if (maybe_t.has_value()) {
                maybe_t.value()->assign(wi);
            }
            return false;
        }

      private:
        std::optional<Worker*> getIdleWorker() {
            if (idle_workers_.empty())
                return std::nullopt;

            auto* w = idle_workers_.front();
            idle_workers_.pop();

            return w;
        };

      private:
        std::queue<Worker*>                 idle_workers_{};
        std::queue<Worker*>                 busy_workers_{};
        static constexpr auto               NUM_MAX_WORKERS{5};
        std::array<Worker, NUM_MAX_WORKERS> workers_{};
    };

}  // namespace

int main() {

    return 0;
}
