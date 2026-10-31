#include <atomic>
#include <memory>

template <typename T> class RingBuffer {
  public:
    explicit RingBuffer(size_t capacity)
        : buf_(std::make_unique<T[]>(capacity)), capacity_(capacity) {}

    bool push(const T& item) {
        size_t h = head_.load(std::memory_order_relaxed);
        size_t t = tail_.load(std::memory_order_acquire);
        if (h - t == capacity_) // buffer is full
            return false;

        // capacity_ needs to be power of 2 for this to work
        buf_[h & (capacity_ - 1)] = item;
        head_.store(h + 1, std::memory_order_release);
        return true;
    };

    bool pop(T& out) {
        size_t t = tail_.load(std::memory_order_relaxed);
        size_t h = head_.load(std::memory_order_acquire);
        if (h == t) // buffer is empty
            return false;

        out = buf_[t & (capacity_ - 1)];
        tail_.store(t + 1, std::memory_order_release);
        return true;
    };

    void reset() {
        size_t h = head_.load(std::memory_order_relaxed);
        tail_.store(h, std::memory_order_relaxed);
    };
    bool empty() const {
        size_t h = head_.load(std::memory_order_relaxed);
        size_t t = tail_.load(std::memory_order_relaxed);
        return h == t;
    };
    bool full() const {
        size_t h = head_.load(std::memory_order_relaxed);
        size_t t = tail_.load(std::memory_order_relaxed);
        return h - t == capacity_;
    };
    size_t capacity() const { return capacity_; };

  private:
    std::unique_ptr<T[]> buf_;
    size_t capacity_ = 0;
    std::atomic<size_t> head_ = 0;
    std::atomic<size_t> tail_ = 0;
    bool full_ = false;
};