#include <catch2/catch.hpp>
#include <utilities/containers/math_set/math_set.hpp>
#include <vector>

using namespace utilities;
using vector_t = std::vector<int>;
using set_t    = MathSet<int>;

template<typename T, typename U>
static void compare_math_set(T&& math_set, U&& corr) {
    REQUIRE(math_set.size() == corr.size());
    REQUIRE(math_set.empty() == corr.empty());
    std::size_t counter = 0;
    auto elem_itr       = math_set.begin();
    for(auto x : corr) {
        REQUIRE(math_set.count(x) == 1);
        REQUIRE(math_set[counter] == x);
        REQUIRE(*elem_itr == x);
        ++counter;
        ++elem_itr;
    }
}

TEST_CASE("MathSet<int> default ctor") {
    set_t s;
    compare_math_set(s, vector_t{});
    REQUIRE(s.begin() == s.end());
    REQUIRE(s.cbegin() == s.cend());
}

TEST_CASE("MathSet<int> initializer list ctor") {
    SECTION("Empty list") {
        MathSet s(std::initializer_list<int>{});
        compare_math_set(s, vector_t{});
    }
    SECTION("Single entry") {
        SECTION("Non-MathSet content") {
            MathSet s{1};
            compare_math_set(s, vector_t{1});
        }
        SECTION("MathSet content") {
            MathSet<set_t> s{set_t{1, 2}};
            REQUIRE(s.size() == 1);
            REQUIRE_FALSE(s.empty());
            compare_math_set(s[0], vector_t{1, 2});
            compare_math_set(*s.begin(), vector_t{1, 2});
            REQUIRE(s.count(set_t{1, 2}) == 1);
        }
    }

    SECTION("Multiple entries") {
        SECTION("Non-MathSet content") {
            MathSet s{1, 2, 3};
            compare_math_set(s, vector_t{1, 2, 3});
        }
        SECTION("MathSet content") {
            MathSet s{set_t{1}, set_t{2, 3}, set_t{}};
            REQUIRE(s.size() == 3);
            compare_math_set(s[0], vector_t{1});
            compare_math_set(s[1], vector_t{2, 3});
            compare_math_set(s[2], vector_t{});
            REQUIRE(s.count(set_t{1}) == 1);
            REQUIRE(s.count(set_t{2, 3}) == 1);
            REQUIRE(s.count(set_t{}) == 1);
        }
    }
}

TEST_CASE("MathSet<int> range ctor") {
    SECTION("Empty list") {
        vector_t v;
        MathSet s(v.begin(), v.end());
        compare_math_set(s, v);
    }
    SECTION("Non-MathSet content") {
        vector_t v{1, 2, 3};
        MathSet s(v.begin(), v.end());
        compare_math_set(s, v);
    }
    SECTION("MathSet content") {
        std::vector v{set_t{1}, set_t{2, 3}, set_t{}};
        MathSet s(v.begin(), v.end());
        compare_math_set(s[0], vector_t{1});
        compare_math_set(s[1], vector_t{2, 3});
        compare_math_set(s[2], vector_t{});
    }
}

TEST_CASE("MathSet copy ctor") {
    SECTION("Normal elements") {
        MathSet s{1, 2, 3};
        MathSet s2(s);
        compare_math_set(s2, vector_t{1, 2, 3});
        for(std::size_t i = 0; i < 3; ++i) REQUIRE(&s2[i] != &s[i]);
    }
    SECTION("MathSet elements") {
        MathSet s{set_t{1}, set_t{}};
        MathSet s2{s};
        compare_math_set(s2[0], vector_t{1});
        compare_math_set(s2[1], vector_t{});
        for(std::size_t i = 0; i < 2; ++i) REQUIRE(&s2[i] != &s[i]);
    }
}

TEST_CASE("MathSet begin") {
    MathSet s{1, 2, 3};
    auto itr = s.begin();

    SECTION("State") {
        for(int i = 1; i < 4; ++i, ++itr) REQUIRE(*itr == i);
    }
    SECTION("Writable") {
        *s.begin() = 9;
        REQUIRE(s[0] == 9);
    }
}

TEST_CASE("MathSet begin const") {
    const MathSet s{1, 2, 3};
    auto itr = s.begin();

    SECTION("State") {
        for(int i = 1; i < 4; ++i, ++itr) REQUIRE(*itr == i);
    }
    SECTION("Read-only") {
        using no_ref = std::remove_reference_t<decltype(*itr)>;
        STATIC_REQUIRE(std::is_const_v<no_ref>);
    }
}

TEST_CASE("MathSet cbegin") {
    MathSet s{1, 2, 3};
    auto itr = s.cbegin();

    SECTION("State") {
        for(int i = 1; i < 4; ++i, ++itr) REQUIRE(*itr == i);
    }
    SECTION("Read-only") {
        using no_ref = std::remove_reference_t<decltype(*itr)>;
        STATIC_REQUIRE(std::is_const_v<no_ref>);
    }
}

TEST_CASE("MathSet end") {
    MathSet s{1, 2};
    auto itr = s.begin();
    REQUIRE_FALSE(itr == s.end());
    ++itr;
    REQUIRE_FALSE(itr == s.end());
    ++itr;
    REQUIRE(itr == s.end());
}

TEST_CASE("MathSet end const") {
    const MathSet s{1, 2};
    auto itr = s.begin();
    REQUIRE_FALSE(itr == s.end());
    ++itr;
    REQUIRE_FALSE(itr == s.end());
    ++itr;
    REQUIRE(itr == s.end());
}

TEST_CASE("MathSet cend") {
    MathSet s{1, 2};
    auto itr = s.cbegin();
    REQUIRE_FALSE(itr == s.cend());
    ++itr;
    REQUIRE_FALSE(itr == s.cend());
    ++itr;
    REQUIRE(itr == s.cend());
}

TEST_CASE("MathSet operator[]") {
    MathSet s{1, 2, 3};

    SECTION("State") {
        REQUIRE(s[0] == 1);
        REQUIRE(s[1] == 2);
        REQUIRE(s[2] == 3);
    }
    SECTION("Writable") {
        s[0] = 9;
        REQUIRE(s[0] == 9);
    }
}

TEST_CASE("MathSet operator[] const") {
    const MathSet s{1, 2, 3};

    SECTION("State") {
        REQUIRE(s[0] == 1);
        REQUIRE(s[1] == 2);
        REQUIRE(s[2] == 3);
    }
    SECTION("Read-only") {
        using no_ref = std::remove_reference_t<decltype(s[0])>;
        STATIC_REQUIRE(std::is_const_v<no_ref>);
    }
}

TEST_CASE("MathSet count") {
    MathSet s{1, 2, 3};
    REQUIRE(s.count(1) == 1);
    REQUIRE(s.count(0) == 0);
}

TEST_CASE("MathSet size") {
    set_t s;
    REQUIRE(s.size() == 0);
    s.push_back(1);
    REQUIRE(s.size() == 1);
}

TEST_CASE("MathSet empty") {
    set_t s;
    REQUIRE(s.empty());
    s.push_back(2);
    REQUIRE_FALSE(s.empty());
}

TEST_CASE("MathSet push_back(elem)") {
    set_t s;
    REQUIRE(s.size() == 0);
    s.push_back(1);
    REQUIRE(s[0] == 1);
    REQUIRE(s.size() == 1);
    s.push_back(2);
    REQUIRE(s[0] == 1);
    REQUIRE(s[1] == 2);
    REQUIRE(s.size() == 2);
}
