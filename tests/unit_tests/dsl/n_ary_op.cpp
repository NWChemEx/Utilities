/*
 * Copyright 2024 NWChemEx-Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "test_dsl.hpp"
#include <utilities/dsl/add.hpp>
#include <utilities/dsl/function_call.hpp>

/* Testing Strategy.
 *
 * The classes which derive from NAryOp are strong types. We thus only need
 * to test the NAryOp infrastructure through one n-ary derived class for each
 * value of n (we must test through the derived class because of the CRTP
 * usage).
 */

TEMPLATE_LIST_TEST_CASE("NAryOp (N == 2)", "", test_utilities::binary_types) {
    using lhs_type = std::tuple_element_t<0, TestType>;
    using rhs_type = std::tuple_element_t<1, TestType>;

    auto values     = test_utilities::binary_values();
    auto [lhs, rhs] = std::get<TestType>(values);

    utilities::dsl::Add<lhs_type, rhs_type> a_xx(lhs, rhs);
    utilities::dsl::Add<const lhs_type, rhs_type> a_cx(lhs, rhs);
    utilities::dsl::Add<lhs_type, const rhs_type> a_xc(lhs, rhs);
    utilities::dsl::Add<const lhs_type, const rhs_type> a_cc(lhs, rhs);

    SECTION("object()") {
        REQUIRE(a_xx.template object<0>() == lhs);
        REQUIRE(a_cx.template object<0>() == lhs);
        REQUIRE(a_xc.template object<0>() == lhs);
        REQUIRE(a_cc.template object<0>() == lhs);

        REQUIRE(a_xx.template object<1>() == rhs);
        REQUIRE(a_cx.template object<1>() == rhs);
        REQUIRE(a_xc.template object<1>() == rhs);
        REQUIRE(a_cc.template object<1>() == rhs);
    }

    SECTION("object() const") {
        REQUIRE(std::as_const(a_xx).template object<0>() == lhs);
        REQUIRE(std::as_const(a_cx).template object<0>() == lhs);
        REQUIRE(std::as_const(a_xc).template object<0>() == lhs);
        REQUIRE(std::as_const(a_cc).template object<0>() == lhs);

        REQUIRE(std::as_const(a_xx).template object<1>() == rhs);
        REQUIRE(std::as_const(a_cx).template object<1>() == rhs);
        REQUIRE(std::as_const(a_xc).template object<1>() == rhs);
        REQUIRE(std::as_const(a_cc).template object<1>() == rhs);
    }

    SECTION("operator==") {
        SECTION("Same values") {
            utilities::dsl::Add<lhs_type, rhs_type> add2(lhs, rhs);
            REQUIRE(a_xx == add2);
        }

        SECTION("Different const-ness") {
            REQUIRE(a_xx == a_cx);
            REQUIRE(a_xx == a_xc);
            REQUIRE(a_xx == a_cc);
            REQUIRE(a_cx == a_xc);
            REQUIRE(a_cx == a_cc);
            REQUIRE(a_xc == a_cc);
        }

        SECTION("Different values") {
            lhs_type lhs2;
            rhs_type rhs2;
            utilities::dsl::Add<lhs_type, rhs_type> add_l(lhs2, rhs);
            utilities::dsl::Add<lhs_type, rhs_type> add_r(lhs, rhs2);
            REQUIRE_FALSE(a_xx == add_l);
            REQUIRE_FALSE(a_xx == add_r);
        }

        SECTION("Different type") {
            char a = 'a';
            utilities::dsl::Add<char, rhs_type> add_l(a, rhs);
            utilities::dsl::Add<lhs_type, char> add_r(lhs, a);
            REQUIRE_FALSE(a_xx == add_l);
            REQUIRE_FALSE(a_xx == add_r);
        }
    }

    SECTION("operator!=") {
        // Just negates operator== so spot check
        lhs_type lhs2;
        utilities::dsl::Add<lhs_type, rhs_type> add_r(lhs2, rhs);
        REQUIRE_FALSE(a_xx != a_cx);
        REQUIRE(a_xx != add_r);
    }
}

TEST_CASE("NAryOp (N == 3)") {
    using utilities::dsl::FunctionCall;
    using type0 = double;
    using type1 = std::vector<int>;
    using type2 = std::map<double, int>;

    auto values = test_utilities::unary_values();
    auto v0     = std::get<type0>(values);
    auto v1     = std::get<type1>(values);
    auto v2     = std::get<type2>(values);

    FunctionCall<type0, type1, type2> a_xxx(v0, v1, v2);
    FunctionCall<const type0, type1, type2> a_cxx(v0, v1, v2);
    FunctionCall<type0, const type1, type2> a_xcx(v0, v1, v2);
    FunctionCall<type0, type1, const type2> a_xxc(v0, v1, v2);
    FunctionCall<const type0, const type1, type2> a_ccx(v0, v1, v2);
    FunctionCall<const type0, type1, const type2> a_cxc(v0, v1, v2);
    FunctionCall<type0, const type1, const type2> a_xcc(v0, v1, v2);
    FunctionCall<const type0, const type1, const type2> a_ccc(v0, v1, v2);

    SECTION("object()") {
        REQUIRE(a_xxx.template object<0>() == v0);
        REQUIRE(a_cxx.template object<0>() == v0);
        REQUIRE(a_xcx.template object<0>() == v0);
        REQUIRE(a_xxc.template object<0>() == v0);
        REQUIRE(a_ccx.template object<0>() == v0);
        REQUIRE(a_cxc.template object<0>() == v0);
        REQUIRE(a_xcc.template object<0>() == v0);
        REQUIRE(a_ccc.template object<0>() == v0);

        REQUIRE(a_xxx.template object<1>() == v1);
        REQUIRE(a_cxx.template object<1>() == v1);
        REQUIRE(a_xcx.template object<1>() == v1);
        REQUIRE(a_xxc.template object<1>() == v1);
        REQUIRE(a_ccx.template object<1>() == v1);
        REQUIRE(a_cxc.template object<1>() == v1);
        REQUIRE(a_xcc.template object<1>() == v1);
        REQUIRE(a_ccc.template object<1>() == v1);

        REQUIRE(a_xxx.template object<2>() == v2);
        REQUIRE(a_cxx.template object<2>() == v2);
        REQUIRE(a_xcx.template object<2>() == v2);
        REQUIRE(a_xxc.template object<2>() == v2);
        REQUIRE(a_ccx.template object<2>() == v2);
        REQUIRE(a_cxc.template object<2>() == v2);
        REQUIRE(a_xcc.template object<2>() == v2);
        REQUIRE(a_ccc.template object<2>() == v2);
    }

    SECTION("object() const") {
        REQUIRE(std::as_const(a_xxx).template object<0>() == v0);
        REQUIRE(std::as_const(a_cxx).template object<0>() == v0);
        REQUIRE(std::as_const(a_xcx).template object<0>() == v0);
        REQUIRE(std::as_const(a_xxc).template object<0>() == v0);
        REQUIRE(std::as_const(a_ccx).template object<0>() == v0);
        REQUIRE(std::as_const(a_cxc).template object<0>() == v0);
        REQUIRE(std::as_const(a_xcc).template object<0>() == v0);
        REQUIRE(std::as_const(a_ccc).template object<0>() == v0);

        REQUIRE(std::as_const(a_xxx).template object<1>() == v1);
        REQUIRE(std::as_const(a_cxx).template object<1>() == v1);
        REQUIRE(std::as_const(a_xcx).template object<1>() == v1);
        REQUIRE(std::as_const(a_xxc).template object<1>() == v1);
        REQUIRE(std::as_const(a_ccx).template object<1>() == v1);
        REQUIRE(std::as_const(a_cxc).template object<1>() == v1);
        REQUIRE(std::as_const(a_xcc).template object<1>() == v1);
        REQUIRE(std::as_const(a_ccc).template object<1>() == v1);

        REQUIRE(std::as_const(a_xxx).template object<2>() == v2);
        REQUIRE(std::as_const(a_cxx).template object<2>() == v2);
        REQUIRE(std::as_const(a_xcx).template object<2>() == v2);
        REQUIRE(std::as_const(a_xxc).template object<2>() == v2);
        REQUIRE(std::as_const(a_ccx).template object<2>() == v2);
        REQUIRE(std::as_const(a_cxc).template object<2>() == v2);
        REQUIRE(std::as_const(a_xcc).template object<2>() == v2);
        REQUIRE(std::as_const(a_ccc).template object<2>() == v2);
    }

    SECTION("operator==") {
        SECTION("Same values") {
            FunctionCall<type0, type1, type2> op2(v0, v1, v2);
            REQUIRE(a_xxx == op2);
        }

        SECTION("Different const-ness") {
            REQUIRE(a_xxx == a_cxx);
            REQUIRE(a_xxx == a_xcx);
            REQUIRE(a_xxx == a_xxc);
            REQUIRE(a_xxx == a_ccx);
            REQUIRE(a_xxx == a_cxc);
            REQUIRE(a_xxx == a_ccx);
            REQUIRE(a_xxx == a_ccc);
        }

        SECTION("Different values") {
            type0 v02;
            type1 v12;
            type2 v22;
            FunctionCall<type0, type1, type2> op0(v02, v1, v2);
            FunctionCall<type0, type1, type2> op1(v0, v12, v2);
            FunctionCall<type0, type1, type2> op2(v0, v1, v22);
            REQUIRE_FALSE(a_xxx == op0);
            REQUIRE_FALSE(a_xxx == op1);
            REQUIRE_FALSE(a_xxx == op2);
        }

        SECTION("Different type") {
            char a = 'a';
            FunctionCall<char, type1, type2> op0(a, v1, v2);
            FunctionCall<type0, char, type2> op1(v0, a, v2);
            FunctionCall<type0, type1, char> op2(v0, v1, a);
            REQUIRE_FALSE(a_xxx == op0);
            REQUIRE_FALSE(a_xxx == op1);
            REQUIRE_FALSE(a_xxx == op2);
        }
    }

    SECTION("operator!=") {
        // Just negates operator== so spot check
        type0 v02;
        FunctionCall<type0, type1, type2> op0(v02, v1, v2);
        REQUIRE_FALSE(a_xxx != a_cxx);
        REQUIRE(a_xxx != op0);
    }
}