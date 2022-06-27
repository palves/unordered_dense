#include <ankerl/unordered_dense_map.h>

#include <doctest.h>

TEST_CASE("iterators_empty") {
    for (size_t i = 0; i < 10; ++i) {
        auto m = ankerl::unordered_dense_map<uint64_t, size_t>();
        REQUIRE(m.begin() == m.end());

        REQUIRE(m.end() == m.find(132));

        m[1];
        REQUIRE(m.begin() != m.end());
        REQUIRE(++m.begin() == m.end());
        m.clear();

        REQUIRE(m.begin() == m.end());
    }
}