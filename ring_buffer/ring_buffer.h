#include <atomic>
#include <memory>

template <typename T> class RingBuffer {
  public:
    explicit RingBuffer(size_t capacity)
        : buf_(std::make_unique<T[]>(capacity)), capacity_(capacity) {}
    bool push(const T& item) {
        size_t h = head_.load(std::memory_order_relaxed);
        size_t t = tail_.load(std::memory_order_acquire);
        if (h - t == capacity) // it is full
            return false;

        buf_[h] = item;
    };
    bool pop(T& out) {};
    void reset() {};
    bool empty() const { return false; };
    bool full() const { return false; };
    size_t size() const { return 0; };
    size_t capacity() const { return 0; };

  private:
    std::unique_ptr<T[]> buf_;
    size_t capacity_ = 0;
    std::atomic<size_t> head_ = 0;
    std::atomic<size_t> tail_ = 0;
    bool full_ = false;
};