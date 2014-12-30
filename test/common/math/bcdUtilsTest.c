#include "../../../common/math/bcdUtils.h"

#include "bcdUtilsTest.h"

#include "../../../test/unity/unity.h"

void bcdUtilsTestSuite(void) {
    RUN_TEST(test_bcd2CharToDec);
}

void test_bcd2CharToDec(void) {
    unsigned char actual = bcd2CharToDec(0x28);
    TEST_ASSERT_EQUAL(28, actual);

    actual = bcd2CharToDec(0x00);
    TEST_ASSERT_EQUAL(0, actual);

    actual = bcd2CharToDec(0x10);
    TEST_ASSERT_EQUAL(10, actual);

    actual = bcd2CharToDec(0x65);
    TEST_ASSERT_EQUAL(65, actual);

    actual = bcd2CharToDec(0x32);
    TEST_ASSERT_EQUAL(32, actual);

    actual = bcd2CharToDec(0x99);
    TEST_ASSERT_EQUAL(99, actual);
}