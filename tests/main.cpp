//
// Created by Yaroslav Rebenko on 20.07.2018.
//
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../src/ModuleMonomial.hpp"
#include "../src/Monomial.hpp"
#include "../src/Term.hpp"
#include "../src/ModuleElement.hpp"
#include "../src/Polynomial.hpp"
#include "../src/MonomialOrder.hpp"

bool test_monomial_mul_1() {
    Monomial<int> a = {1, 1, 1};
    Monomial<int> b = {1, 1};
    Monomial<int> c = {2, 2, 1};
    return a * b == c;
}

bool test_monomial_mul_2() {
    Monomial<int> a = {1, 1};
    Monomial<int> b = {1, 1, 1};
    Monomial<int> c = {2, 2, 1};
    return a * b == c;
}

bool test_monomial_mul_3() {
    Monomial<int> a = {1, 1};
    a *= {1, 1, 1};
    Monomial<int> c = {2, 2, 1};
    return a == c;
}

TEST_CASE( "Monomial Mul first dim bigger" ) {
    REQUIRE( test_monomial_mul_1() );
}

TEST_CASE( "Monomial Mul second dim bigger" ) {
    REQUIRE( test_monomial_mul_2() );
}

TEST_CASE( "Monomial Mul assign" ) {
    REQUIRE( test_monomial_mul_3() );
}


bool term_mul_1() {
    Term<double, Monomial<int> > a(1, {1});
    Term<double, Monomial<int> > b(1, {0, 1});
    Term<double, Monomial<int> > c(1, {1, 1});
    return a * b == c;
}

bool term_mul_2() {
    Term<double, Monomial<int> > a(1, {0, 1});
    Term<double, Monomial<int> > b(1, {1});
    Term<double, Monomial<int> > c(1, {1, 1});
    return a * b == c;
}

bool term_mul_3() {
    Term<double, Monomial<int> > a(0, {1});
    Term<double, Monomial<int> > b(1, {0, 1});
    Term<double, Monomial<int> > c(0, {});
    return a * b == c;
}

bool term_sum_1() {
    Term<double, Monomial<int> > a(2, {1});
    Term<double, Monomial<int> > b(1, {1});
    Term<double, Monomial<int> > c(3, {1});
    return a + b == c;
}


TEST_CASE( "Term Mul second dim bigger" ) {
    REQUIRE( term_mul_1() );
}

TEST_CASE( "Term Mul first dim bigger" ) {
    REQUIRE( term_mul_2() );
}

TEST_CASE( "Term Mul zero" ) {
    REQUIRE( term_mul_3() );
}

TEST_CASE( "Term Sum" ) {
    REQUIRE( term_sum_1() );
}


bool polynomial_add_term() {
    Polynomial<double, int> a = {{1, {2, 1}}, {1, {1, 1}}};
    Polynomial<double, int> b = {{1, {1, 1}}};
    a += b[0];
    Polynomial<double, int> c = {{1, {2, 1}}, {2, {1, 1}}};
    return a == c;
}

bool polynomial_mul_term() {
    Polynomial<double, int> a = {{1, {2, 1}}, {1, {1, 1}}};
    Polynomial<double, int> b = {{1, {1, 1}}};
    a *= b[0];
    Polynomial<double, int> c = {{1, {3, 2}}, {1, {2, 2}}};
    return a == c;
}

bool polynomial_add() {
    auto cmp = Lex<int>();
    Polynomial<double, int> a = {{2, {2, 2}}, {1, {1, 1}}};
    Polynomial<double, int> b = {{3, {1, 1}}, {3, {}}};
    a = std::move(add(cmp, a, b));
    Polynomial<double, int> c = {{2, {2, 2}}, {4, {1, 1}}, {3, {}}};
    return a == c;
}

bool polynomial_mul() {
    auto cmp = Lex<int>();
    Polynomial<double, int> a = {{3, {3, 10}}, {1, {2, 1}}, {10, {0, 1}}};
    Polynomial<double, int> b = {{1, {1, 9}}, {1, {}}};
    a = std::move(mul(cmp, a, b));
    Polynomial<double, int> c = {{3, {4, 19}}, {4, {3, 10}}, {1, {2, 1}}, {10, {1, 10}}, {10, {0, 1}}};
    return a == c;
}

TEST_CASE( "Polynomial add assign term" ) {
    REQUIRE( polynomial_add_term() );
}

TEST_CASE( "Polynomial mul assign term") {
    REQUIRE( polynomial_mul_term() );
}

TEST_CASE( "Polynomial add" ) {
    REQUIRE( polynomial_add() );
}

TEST_CASE( "Polynomial mul" ) {
    REQUIRE(polynomial_mul());
}

bool bar() {
    std::vector<Polynomial<double, int>> i = {
            {{1, {}}},
            {{2, {1, 1}}},
            {{-4, {1, 1}}, {-1, {}}},
            {{-1, {1, 1}}}
    };
    ModuleElement<int> e = {
            {{1, {}}, 1},
            {{1, {}}, 2},
            {{-2, {}}, 3}
    };
    auto cmp = Lex<int>();
    auto x = bar(cmp, i, e);
    return x == Polynomial<double, int>({{-1, {}}});
}

TEST_CASE( "Bar" ) {
    REQUIRE( bar() );
}

bool term_gcd() {
    Term<double, Monomial<int> > a(2, {2, 1});
    Term<double, Monomial<int> > b(1, {1, 1});
    Term<double, Monomial<int> > c(1, {1, 1});
    return gcd(a, b) == c;
}

TEST_CASE( "Term gcd" ) {
    REQUIRE( term_gcd() );
}

bool spair() {
    std::vector<Polynomial<double, int>> i = {
            {{1, {}}},
            {{2, {1, 1}}},
            {{-4, {1, 1}}, {-1, {}}},
            {{-1, {1, 1}}}
    };
    ModuleElement<int> e = {
            {{1, {}}, 1},
            {{1, {}}, 2},
            {{-2, {}}, 3}
    };
    ModuleElement<int> e2 = {
            {{1, {}}, 0},
    };
    auto cmp = Lex<int>();
    auto t = spair(i, cmp, e, e2);
    return t == std::make_pair(e * Term<double, Monomial<int>>({-1, {}}), e2);
}

TEST_CASE( "Spair" ) {
    REQUIRE( spair() );
}