#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

int add(int a, int b) {
    return a + b;
}

BOOST_AUTO_TEST_CASE(test_addition) {
    BOOST_CHECK_EQUAL(add(2, 3), 5);
}