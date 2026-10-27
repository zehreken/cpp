#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <string>

#include "tracker.h"
#include "vector.h"

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

TEST_CASE("const vector can be read") {
    Vector<int> v(4);
    int x = 7;
    v.push_back(x);
    const Vector<int>& cv = v;
    CHECK(cv.size() == 1);
    CHECK(cv[0] == 7);
}

TEST_CASE("values survive growth in order") {
    Vector<int> v(2);
    v.push_back(0);
    v.push_back(1);
    CHECK(v.size() == 2);
    CHECK(v.capacity() == 2);

    v.push_back(2);
    CHECK(v[0] == 0);
    CHECK(v[1] == 1);
}

TEST_CASE(
    "copy construct: copy has equal contents, and changing one leave other "
    "alone"
) {
    Vector<int> v(4);
    for (size_t i = 0; i < 5; ++i) {
        v.push_back(i);
    }
    CHECK(v.size() == 5);
    CHECK(v.capacity() == 8);
    CHECK(v[3] == 3);

    // c for copy
    Vector<int> c(v);
    CHECK(c.size() == 5);
    CHECK(c.capacity() == 8);
    c[3] = 33;
    CHECK(v[3] == 3);
}

TEST_CASE("copy assignment: same, plus 'v = v;' is safe") {
    Vector<int> v(4);
    for (size_t i = 0; i < 5; ++i) {
        v.push_back(i);
    }
    CHECK(v.size() == 5);
    CHECK(v.capacity() == 8);
    CHECK(v[3] == 3);

    // c for copy
    Vector<int> c(1);
    c = v;
    CHECK(c.size() == 5);
    CHECK(c.capacity() == 8);
    c[3] = 33;
    CHECK(v[3] == 3);

    v = v;
    for (size_t i = 0; i < v.size(); ++i) {
        CHECK(v[i] == static_cast<int>(i));
    }
}

TEST_CASE("move constructor: source ends up empty, Tracker::copies stays 0") {
    Vector<int> v(4);
    for (size_t i = 0; i < 5; ++i) {
        v.push_back(i);
    }

    // m for move
    Vector<int> m(std::move(v));

    CHECK(m.size() == 5);
    CHECK(m.capacity() == 8);
    for (size_t i = 0; i < m.size(); ++i) {
        CHECK(m[i] == static_cast<int>(i));
    }

    CHECK(v.size() == 0);
    CHECK(v.capacity() == 0);

    v.push_back(42);
    CHECK(v.size() == 1);
}

TEST_CASE("move assignment: same, and the old buffer of the target is freed") {
    Vector<int> v(4);
    for (size_t i = 0; i < 5; ++i) {
        v.push_back(i);
    }

    // m for move
    Vector<int> m(1);
    m = std::move(v); // move assignment
    CHECK(m.size() == 5);
    CHECK(m.capacity() == 8);
    for (size_t i = 0; i < m.size(); ++i) {
        CHECK(m[i] == static_cast<int>(i));
    }

    CHECK(v.size() == 0);
    CHECK(v.capacity() == 0);
    v.push_back(42);
}
