#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include "imp_vector.h"
#include "tracker.h"

TEST_CASE("constructor sets capacity, size starts at 0") {
    ImpVector<int> v(5);
    CHECK(v.size() == 0);
    CHECK(v.capacity() == 5);
}
