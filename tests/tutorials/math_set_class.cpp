#include <catch2/catch.hpp>
#include <utilities/containers/math_set.hpp>

TEST_CASE("MathSet usage") {
    using namespace utilities;

    MathSet<int> s1{1, 2, 3, 4};
    MathSet<int> s2{2, 4, 6, 8};

    // Union of two sets
    MathSet<int> s3 = s1 + s2;
    REQUIRE(s3 == MathSet{1, 2, 3, 4, 6, 8});

    // Intersection
    MathSet<int> s4 = s1 ^ s2;
    REQUIRE(s4 == MathSet{2, 4});

    // Set difference
    MathSet<int> s5 = s1 - s2;
    REQUIRE(s5 == MathSet{1, 3});

    // Possible to avoid copy while slicing:
    const auto& s7 = s1 ^ s2;
    REQUIRE(&s7[0] == &s1[1]);
    REQUIRE(&s7[1] == &s1[3]);

    const auto& s8 = s1 - s2;
    REQUIRE(&s8[0] == &s1[0]);
    REQUIRE(&s8[1] == &s1[2]);

    // Can append new elements
    s1.push_back(5);
    REQUIRE(s1.size() == 5);

    // More complicated slicing (we select the elements of s1 with even values)
    const auto& s9 = s1.select([](const auto& x) { return x % 2 == 0; });
    REQUIRE(&s9[0] == &s1[1]);
    REQUIRE(&s9[1] == &s1[3]);
}