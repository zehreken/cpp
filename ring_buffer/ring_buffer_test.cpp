#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "ring_buffer.h"

TEST_CASE("Capacity is set correctly") {
    RingBuffer<int> rb(128);
    CHECK(rb.capacity() == 128);
}

TEST_CASE("Push") {
    RingBuffer<int> rb(16);
    CHECK(rb.capacity() == 16);

    for (size_t i = 0; i < 8; ++i) {
        CHECK(rb.push(i));
    }
}

TEST_CASE("Pop") {
    RingBuffer<int> rb(16);
    CHECK(rb.empty());
    CHECK(!rb.full());
    CHECK(rb.capacity() == 16);

    for (size_t i = 0; i < 8; ++i) {
        rb.push(i);
    }

    while (!rb.empty()) {
        int item;
        CHECK(rb.pop(item));

        std::cout << item << std::endl;
    }
}