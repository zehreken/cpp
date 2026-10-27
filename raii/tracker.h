#pragma once

// Counts constructions, copies, moves and destructions, so tests can check
// what the vector does to its elements, not just which values end up inside.
struct Tracker {
    static inline int alive = 0, copies = 0, moves = 0;
    int value;

    Tracker(int v = 0) : value(v) { ++alive; }
    Tracker(const Tracker& o) : value(o.value) {
        ++alive;
        ++copies;
    }
    Tracker(Tracker&& o) noexcept : value(o.value) {
        ++alive;
        ++moves;
    }
    Tracker& operator=(const Tracker& o) {
        value = o.value;
        ++copies;
        return *this;
    }
    Tracker& operator=(Tracker&& o) noexcept {
        value = o.value;
        ++moves;
        return *this;
    }
    ~Tracker() { --alive; }

    static void reset() { alive = copies = moves = 0; }
};
