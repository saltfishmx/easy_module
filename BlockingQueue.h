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

    // ��ֹ��������͸�ֵ����
    BlockingQueue(const BlockingQueue&) = delete;
    BlockingQueue& operator=(const BlockingQueue&) = delete;

    // ���һ��Ԫ�ص�����
    void push(const T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        queue_.push(value);
        // ֪ͨһ���ȴ����������߳�
        condition_.notify_one();
    }

    // �Ӷ������Ƴ�������һ��Ԫ��
    T pop() {
        std::unique_lock<std::mutex> lock(mutex_);
        // ������Ϊ�գ��ȴ�ֱ����Ԫ�ر���ӽ���
        condition_.wait(lock, [this] { return !queue_.empty(); });
        T value = queue_.front();
        queue_.pop();
        return value;
    }

    // ��ȡ���еĴ�С
    size_t size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    // �������Ƿ�Ϊ��
    bool empty() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

private:
    mutable std::mutex mutex_;
    std::condition_variable condition_;
    std::queue<T> queue_;
};
