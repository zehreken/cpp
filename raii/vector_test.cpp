#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <string>

#include "vector.h"

// Counts constructions, copies, moves and destructions, so tests can check
// what the vector does to its elements, not just which values end up inside.
struct Tracker {
    static inline int alive = 0, copies = 0, moves = 0;
    int value;

    Tracker(int v = 0) : value(v) { ++alive; }
    Tracker(const Tracker& o) : value(o.value) { ++alive; ++copies; }
    Tracker(Tracker&& o) noexcept : value(o.value) { ++alive; ++moves; }
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

TEST_CASE("constructor sets capacity, size starts at 0") {
    Vector<int> v(5);
    CHECK(v.size() == 0);
    CHECK(v.capacity() == 5);
}

TEST_CASE("capacity 0 still allows push_back") {
    Vector<int> v(0);
    int x = 42;
    v.push_back(x);
    CHECK(v.size() == 1);
    CHECK(v.capacity() >= 1);
}

TEST_CASE("push_back past capacity keeps size and doubles capacity") {
    Vector<std::string> v(1);
    for (int i = 0; i < 1000; ++i) {
        std::string s = std::string(40, 'x') + std::to_string(i);
        v.push_back(s);
    }
    CHECK(v.size() == 1000);
    CHECK(v.capacity() == 1024);
}

TEST_CASE("reserve smaller than capacity does nothing") {
    Vector<int> v(10);
    v.reserve(5);
    CHECK(v.capacity() == 10);
}

TEST_CASE("growing moves elements instead of copying them") {
    Tracker::reset();
    {
        Vector<Tracker> v(2);
        Tracker a(1), b(2);
        v.push_back(a);
        v.push_back(b);

        int copies_before = Tracker::copies;
        v.reserve(16);
        CHECK(Tracker::copies == copies_before);
        CHECK(Tracker::moves >= 2);
    }
    CHECK(Tracker::alive == 0); // nothing leaked, nothing destroyed twice
}

// TODO: there is no operator[] yet, so no test can check that values survive
// growth in the right order. Add one, then write that test.

// TODO (Rule of 5): write these before implementing the members.
//   - copy constructor: copy has equal contents, and changing one leaves the
//     other alone
//   - copy assignment: same, plus `v = v;` is safe
//   - move constructor: source ends up empty, Tracker::copies stays 0
//   - move assignment: same, and the old buffer of the target is freed
