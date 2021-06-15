#include "NumberWithUnits.hpp"
#include "doctest.h"
#include <string>
#include <iostream>

using namespace std;
using namespace ariel;

TEST_CASE("constructor") {
    NumberWithUnits n1;
    NumberWithUnits n2 (1.4, "sec");
    NumberWithUnits n3 (33.3, "USD");
    CHECK(n1.getValue() == 0.0);
    CHECK(n1.getUnit() == "km");
    CHECK(n2.getValue() == 1.4);
    CHECK(n2.getUnit() == "sec");
    CHECK(n3.getValue() == 33.3);
    CHECK(n3.getUnit() == "USD");
}

TEST_CASE("==")
{
    NumberWithUnits a,b; 
    CHECK(a==(b));
    a.setValue(5);
    b.setValue(5);
    CHECK(b == a);
}

TEST_CASE("throw") 
{
    NumberWithUnits a;
    NumberWithUnits b (1,"sec");
    NumberWithUnits c (1,"kg");
    NumberWithUnits d (1,"USD");
    CHECK_THROWS(a.operator<=(c));
    CHECK_THROWS(a.operator<=(b));
    CHECK_THROWS(a.operator<=(d));
    CHECK_THROWS(b.operator<=(b));
    CHECK_THROWS(b.operator<=(d));
    CHECK_THROWS(d.operator<=(b));
    CHECK_THROWS(a.operator<(c));
    CHECK_THROWS(a.operator<(b));
    CHECK_THROWS(a.operator<(d));
    CHECK_THROWS(b.operator<(b));
    CHECK_THROWS(b.operator<(d));
    CHECK_THROWS(d.operator<(b));
    CHECK_THROWS(a.operator>=(c));
    CHECK_THROWS(a.operator>=(b));
    CHECK_THROWS(a.operator>=(d));
    CHECK_THROWS(b.operator>=(b));
    CHECK_THROWS(b.operator>=(d));
    CHECK_THROWS(d.operator>=(b));
    CHECK_THROWS(a.operator>(c));
    CHECK_THROWS(a.operator>(b));
    CHECK_THROWS(a.operator>(d));
    CHECK_THROWS(b.operator>(b));
    CHECK_THROWS(b.operator>(d));
    CHECK_THROWS(d.operator>(b));
    CHECK_THROWS(a.operator!=(c));
    CHECK_THROWS(a.operator!=(b));
    CHECK_THROWS(a.operator!=(d));
    CHECK_THROWS(b.operator!=(b));
    CHECK_THROWS(b.operator!=(d));
    CHECK_THROWS(d.operator!=(b));
    CHECK_THROWS(a.operator+(c));
    CHECK_THROWS(a.operator+(b));
    CHECK_THROWS(a.operator+(d));
    CHECK_THROWS(b.operator+(b));
    CHECK_THROWS(b.operator+(d));
    CHECK_THROWS(d.operator+(b));
    CHECK_THROWS(a.operator-(c));
    CHECK_THROWS(a.operator-(b));
    CHECK_THROWS(a.operator-(d));
    CHECK_THROWS(b.operator-(b));
    CHECK_THROWS(b.operator-(d));
    CHECK_THROWS(d.operator-(b));
    CHECK_THROWS(a.operator==(c));
    CHECK_THROWS(a.operator==(b));
    CHECK_THROWS(a.operator==(d));
    CHECK_THROWS(b.operator==(b));
    CHECK_THROWS(b.operator==(d));
    CHECK_THROWS(d.operator==(b));
    CHECK_THROWS(a.operator+=(c));
    CHECK_THROWS(a.operator+=(b));
    CHECK_THROWS(a.operator+=(d));
    CHECK_THROWS(b.operator+=(b));
    CHECK_THROWS(b.operator+=(d));
    CHECK_THROWS(d.operator+=(b));
    CHECK_THROWS(a.operator-=(c));
    CHECK_THROWS(a.operator-=(b));
    CHECK_THROWS(a.operator-=(d));
    CHECK_THROWS(b.operator-=(b));
    CHECK_THROWS(b.operator-=(d));
    CHECK_THROWS(d.operator-=(b));
}