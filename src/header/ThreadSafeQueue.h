/**
 * @file ThreadSafeQueue.h
 * @brief Thread safe queue
 * @version 0.1
 * @date 13/04/2024
 * @author Jakub Všetečka
 */

#ifndef THREAD_SAFE_QUEUE_H
#define THREAD_SAFE_QUEUE_H

#include <condition_variable>
#include <exception>
#include <mutex>
#include <queue>

/**
 * @brief Thread safe queue
 *
 * @tparam T
 */
template <typename T>
class ThreadSafeQueue {
  private:
    std::queue<T> queue;
    mutable std::mutex mtx;
    std::condition_variable cond;

  public:
    ThreadSafeQueue() {}

    // Delete copy constructor and assignment operation
    ThreadSafeQueue(const ThreadSafeQueue<T> &) = delete;
    ThreadSafeQueue &operator=(const ThreadSafeQueue<T> &) = delete;

    /**
     * @brief Push an element to the queue
     *
     * @param value
     * @return void
     */
    void push(T value) {
        std::lock_guard<std::mutex> lock(mtx);
        queue.push(std::move(value));
        cond.notify_one();
    }

    /**
     * @brief Pop an element from the queue
     *
     * @return T
     */
    T pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cond.wait(lock, [this] { return !queue.empty(); });
        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    /**
     * @brief Try to pop an element from the queue
     *
     * @param value
     * @return bool
     */
    bool try_pop(T &value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (queue.empty()) {
            return false;
        }
        value = std::move(queue.front());
        queue.pop();
        return true;
    }

    /**
     * @brief Check if the queue is empty
     *
     * @return bool
     */
    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }

    /**
     * @brief Get the size of the queue
     *
     * @return size_t
     */
    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.size();
    }
};

#endif // THREAD_SAFE_QUEUE_H
