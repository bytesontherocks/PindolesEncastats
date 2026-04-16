// Enhanced thread-safe queue variant.
//
// Usage:
// - addItem(value) / addItem(std::move(value)) pushes and notifies one waiter.
// - copyItem() blocks until non-empty, then copies and pops front.
// - copyItemFor(timeout) waits up to timeout; returns std::nullopt on timeout.
// - getIf(pred) is non-blocking: if queue is non-empty and pred(front) is true, it moves+pops
//   front and returns std::optional<T>{item}; otherwise std::nullopt.
// - waitAndGetIf(pred) blocks until queue is non-empty and pred(front) is true, then moves+pops
//   front and returns it.
// - waitAndGetIfFor(timeout, pred) waits up to timeout for pred(front); returns std::nullopt on
//   timeout.
// Note: getIf/waitAndGetIf check only the current front element (FIFO semantics); they do not
// scan deeper items.
#pragma once

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <optional>
#include <queue>
#include <utility>

template <typename T>
class ThreadSafeQueueV2 {
  public:
    void addItem(const T& item) {
        {
            std::lock_guard lock(m_mutex);
            m_q.push(item);
        }

        m_cv.notify_one();
    }

    void addItem(T&& item) {
        {
            std::lock_guard lock(m_mutex);
            m_q.push(std::move(item));
        }

        m_cv.notify_one();
    }

    T copyItem() {
        std::unique_lock lock(m_mutex);
        m_cv.wait(lock, [&] { return !m_q.empty(); });
        const auto item = m_q.front();
        m_q.pop();
        return item;
    }

    template <typename Rep, typename Period>
    std::optional<T> copyItemFor(const std::chrono::duration<Rep, Period>& timeout) {
        std::unique_lock lock(m_mutex);
        if (!m_cv.wait_for(lock, timeout, [&] { return !m_q.empty(); })) {
            return std::nullopt;
        }

        T item = std::move(m_q.front());
        m_q.pop();
        return item;
    }

    template <typename Predicate>
    std::optional<T> getIf(Predicate&& pred) {
        std::lock_guard lock(m_mutex);
        if (m_q.empty()) {
            return std::nullopt;
        }

        if (!std::forward<Predicate>(pred)(m_q.front())) {
            return std::nullopt;
        }

        T item = std::move(m_q.front());
        m_q.pop();
        return item;
    }

    template <typename Predicate>
    T waitAndGetIf(Predicate&& pred) {
        std::unique_lock lock(m_mutex);
        m_cv.wait(lock, [&] { return !m_q.empty() && pred(m_q.front()); });

        T item = std::move(m_q.front());
        m_q.pop();
        return item;
    }

    template <typename Rep, typename Period, typename Predicate>
    std::optional<T> waitAndGetIfFor(const std::chrono::duration<Rep, Period>& timeout,
                                     Predicate&&                              pred) {
        std::unique_lock lock(m_mutex);
        if (!m_cv.wait_for(lock, timeout, [&] { return !m_q.empty() && pred(m_q.front()); })) {
            return std::nullopt;
        }

        T item = std::move(m_q.front());
        m_q.pop();
        return item;
    }

  private:
    std::mutex              m_mutex;
    std::condition_variable m_cv;
    std::queue<T>           m_q;
};
