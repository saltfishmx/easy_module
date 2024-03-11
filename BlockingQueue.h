#pragma once
#include <condition_variable>
#include <mutex>
#include <queue>
#include <exception>
template <typename T>
class BlockingQueue {
public:
    BlockingQueue() = default;
    ~BlockingQueue() = default;

    // 禁止拷贝构造和赋值操作
    BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue& operator=(const BlockingQueue&) = delete;

    // 添加一个元素到队列
    void push(const T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(value);
        // 通知一个等待的消费者线程
        condition_.notify_one();
    }

    // 从队列中移除并返回一个元素
    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        // 当队列为空，等待直到有元素被添加进来
        condition_.wait(lock, [this] { return !queue_.empty(); });
        T value = queue_.front();
        queue_.pop();
        return value;
    }

    // 获取队列的大小
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    // 检查队列是否为空
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    mutable std::mutex mutex_;
    std::condition_variable condition_;
    std::queue<T> queue_;
};
