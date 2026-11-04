#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "linked_list.hpp"

TEST_CASE("Init works, size is correct") {
    LinkedList list{0};
    CHECK(list.get_size() == 1);
}

TEST_CASE("Push increases size") {
    LinkedList list{0};
    for (size_t i = 1; i < 10; ++i) {
        list.push(i + 1);
    }
    CHECK(list.get_size() == 10);
}

TEST_CASE("Pop") {
    LinkedList list{0};
    for (size_t i = 1; i < 6; ++i) {
        list.push(i);
    }
    CHECK(list.get_size() == 6);

    for (size_t i = 5; i > 0; --i) {
        int v;
        list.pop(v);
        CHECK(v == i);
    }
}

TEST_CASE("Insert") {
    LinkedList list{0};
    for (size_t i = 1; i < 6; ++i) {
        list.push(i);
    }
    CHECK(list.get_size() == 6);

    list.insert(42, 2);
    // while (list.get_size() > 0) {
    //     int a;
    //     list.pop(a);
    //     list.print();
    // }
}

TEST_CASE("Remove") {
    LinkedList list{0};
    for (size_t i = 1; i < 6; ++i) {
        list.push(i);
    }
    CHECK(list.get_size() == 6);

    list.print();
    list.remove(0);
    list.print();

    list.remove(2);
    list.remove(1);
    list.print();
}