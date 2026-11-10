#include <cstdio>
#include <functional>
#include <vector>

// A tiny timer system from a game engine. Game code schedules callbacks
// to run after a delay; the engine calls Update(dt) once per frame.
namespace original {
class TimerManager {
  public:
    void schedule_after(float delay, std::function<void()> callback) {
        timers_.push_back({delay, std::move(callback)});
    }

    void update(float dt) {
        for (auto& t : timers_) {
            t.remaining_ -= dt;
            if (t.remaining_ <= 0.f) {
                t.callback_();
            }
        }
        // remove expired timers
        std::vector<Timer> alive;
        for (auto& t : timers_)
            if (t.remaining_ > 0.f)
                alive.push_back(t);
        timers_ = alive;
    }

    size_t count() const { return timers_.size(); }

  private:
    struct Timer {
        float remaining_;
        std::function<void()> callback_;
    };
    std::vector<Timer> timers_;
};

void run() {
    TimerManager tm;
    int frame = 0;

    // A repeating "heartbeat" that reschedules itself from inside its callback.
    std::function<void()> heartbeat = [&] {
        std::printf("frame %d: heartbeat\n", frame);
        tm.schedule_after(0.05f, heartbeat);
    };
    tm.schedule_after(0.05f, heartbeat);
    tm.schedule_after(0.05f, [&] {
        std::printf("frame %d: reload done\n", frame);
    });
    tm.schedule_after(0.10f, [&] {
        std::printf("frame %d: grenade explodes\n", frame);
    });
    tm.schedule_after(1.00f, [&] {
        std::printf("frame %d: respawn\n", frame);
    });

    for (frame = 1; frame <= 6; ++frame)
        tm.update(1.f / 60.f);

    std::printf("timers left: %zu\n", tm.count());
}
} // namespace original

namespace improved {
struct TimerHandle {
    uint32_t index_;

    bool operator==(const TimerHandle other) {
        return this->index_ == other.index_;
    }
};

class TimerManager {
  public:
    TimerHandle schedule_after(float delay, std::function<void()> callback) {
        TimerHandle h{timer_index_++};
        pending_.push_back(
            {delay, std::move(callback), h, false}
        ); // h is copied

        return h; // h is also copied, which should be fine
    }

    void cancel(TimerHandle handle) {
        // cancel has a similar problem as schedule, erasing from timers might
        // invalidate refs in update, erase does not reallocate actually but it
        // shifts the elements
        for (auto& t : timers_) {
            if (t.handle_ == handle) {
                t.is_cancelled_ = true;
                break; // exit early
            }
        }
    }

    void update(double dt) {
        if (!pending_
                 .empty()) { // is this a good check, might save a few cycles
            timers_.insert(timers_.begin(), pending_.begin(), pending_.end());
            pending_.clear();
        }
        for (auto& t : timers_) {
            t.remaining_ -= dt;
            if (t.remaining_ <= 0.f) {
                t.callback_();
            }
        }
        // remove expired timers
        // std::vector<Timer> alive;
        // for (auto& t : timers_)
        //     if (t.remaining_ > 0.f)
        //         alive.push_back(t);
        // timers_ = alive;
        // this should fix the allocator
        for (size_t i = 0; i < timers_.size();) {
            if (timers_[i].remaining_ <= 0.0f || timers_[i].is_cancelled_) {
                timers_.erase(timers_.begin() + i);
            } else {
                ++i;
            }
        }
    }

    size_t count() const { return timers_.size(); }

  private:
    struct Timer {
        double remaining_; // changed to double, high precision fixed grenade
        std::function<void()> callback_;
        TimerHandle handle_;
        bool is_cancelled_ = false;
    };
    std::vector<Timer> timers_;
    std::vector<Timer> pending_;
    uint32_t timer_index_ = 0;
};

void run() {
    TimerManager tm;
    int frame = 0;

    // A repeating "heartbeat" that reschedules itself from inside its callback.
    std::function<void()> heartbeat = [&] {
        std::printf("frame %d: heartbeat\n", frame);
        tm.schedule_after(0.05f, heartbeat);
    };
    auto heartbeat_handle = tm.schedule_after(0.05f, heartbeat);
    tm.schedule_after(0.05f, [&] {
        std::printf("frame %d: reload done\n", frame);
    });
    tm.schedule_after(0.10f, [&] {
        std::printf("frame %d: grenade explodes\n", frame);
    });
    auto respawn_handle = tm.schedule_after(1.00f, [&] {
        std::printf("frame %d: respawn\n", frame);
    });

    for (frame = 1; frame <= 60; ++frame) {
        if (frame == 30) {
            tm.cancel(
                heartbeat_handle
            ); // this does not work because, no handle is stored from the
               // lambda function
            tm.cancel(respawn_handle); // this one works
        }
        tm.update(1.f / 60.f);
    }

    std::printf("timers left: %zu\n", tm.count());
}
} // namespace improved

int main() {
    // original::run();
    improved::run();
}