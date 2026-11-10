#include <atomic>
#include <cstdio>
#include <thread>

// Lock-free single-producer / single-consumer queue.
// The game thread pushes audio commands; the audio thread pops them.
namespace original {
struct AudioCommand {
    int voice_id_;
    float volume_;
};

template <typename T, size_t Capacity> class SpscQueue {
  public:
    bool push(const T& item) {
        size_t h = head_.load(std::memory_order_relaxed);
        size_t next = (h + 1) % Capacity;
        if (next == tail_.load(std::memory_order_relaxed))
            return false; // full
        buffer_[h] = item;
        head_.store(next, std::memory_order_relaxed);
        return true;
    }

    bool pop(T& out) {
        size_t t = tail_.load(std::memory_order_relaxed);
        if (t == head_.load(std::memory_order_relaxed))
            return false; // empty
        out = buffer_[t];
        tail_.store((t + 1) % Capacity, std::memory_order_relaxed);
        return true;
    }

  private:
    T buffer_[Capacity];
    std::atomic<size_t> head_{0}; // written by producer
    std::atomic<size_t> tail_{0}; // written by consumer
};

void run() {
    SpscQueue<AudioCommand, 1000> queue;
    constexpr int n = 10'000'000;

    std::thread producer([&] {
        for (int i = 0; i < n; ++i)
            while (!queue.push({i, i * 0.5f})) {
            }
    });

    long long sum = 0;
    int bad = 0;
    std::thread consumer([&] {
        AudioCommand cmd;
        for (int i = 0; i < n; ++i) {
            while (!queue.pop(cmd)) {
            }
            if (cmd.voice_id_ != i)
                ++bad;
            sum += cmd.voice_id_;
        }
    });

    producer.join();
    consumer.join();
    std::printf(
        "sum %lld (expected %lld), out of order: %d\n",
        sum,
        (long long)n * (n - 1) / 2,
        bad
    );
}
} // namespace original

int main() { original::run(); }