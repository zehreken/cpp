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
} // namespace improved

int main() {
    original::run();
    improved::run();
}