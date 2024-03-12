// Original from: https://codereview.stackexchange.com/questions/267847/thread-safe-message-m_q
#include <queue> 
#include <mutex> 
#include <condition_variable>

template <typename T>
class ThreadSafeQueue {
public:
    void addItem(T&& item) {
        {
            std::lock_guard lock(m_mutex);
            m_q.push(item);
        }

        m_cv.notify_one();
    }

    // returns reference to the first element
    T& getItem() {
        std::unique_lock lock(m_mutex);
        m_cv.wait(lock, [&]{ return !m_q.empty(); });
        return m_q.front();
    }

    // removes first element
    void removeItem() {
        std::lock_guard lock(m_mutex);
        m_q.pop();
    }

    T  copyItem() {
        std::unique_lock lock(m_mutex);
        m_cv.wait(lock, [&]{ return !m_q.empty(); });
        const auto item = m_q.front();
        m_q.pop();
        return item;
    }
private:
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::queue<T> m_q;
};