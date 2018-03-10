#include "../../../common/math/hexUtils.h"

#include "hexUtilsTest.h"

#include "../../../test/unity/unity.h"

// ALL TESTS

void hexUtilsTestSuite(void) {
    RUN_TEST(test_hex2CharToInt_should_equal_to_0_if_0);
    RUN_TEST(test_hex2CharToInt_should_equal_to_197_if_C5);
    RUN_TEST(test_hex2CharToInt_should_equal_to_255_if_FF);

    RUN_TEST(test_hex4CharToLong_should_equal_to_0_if_0);
    RUN_TEST(test_hex2CharToLong_should_equal_to_0_if_D4B3);
    RUN_TEST(test_hex2CharToLong_should_equal_to_0_if_FFFF);

    RUN_TEST(hex6CharToLong_should_equal_to_0_if_0);
    RUN_TEST(hex6CharToLong_should_equal_to_1193046_if_123456);
    RUN_TEST(hex6CharToLong_should_equal_to_16777215_if_FFFFFF);
}

// hex2CharToInt

void test_hex2CharToInt_should_equal_to_0_if_0(void) {
    int actual = hex2CharToInt(0, 0);

    TEST_ASSERT_EQUAL(0, actual);
}

void test_hex2CharToInt_should_equal_to_197_if_C5(void) {
    int actual = hex2CharToInt(0xC, 0x05);

    TEST_ASSERT_EQUAL(197, actual);
}

void test_hex2CharToInt_should_equal_to_255_if_FF(void) {
    int actual = hex2CharToInt(0x0F, 0x0F);

    TEST_ASSERT_EQUAL(255, actual);
}

// hex4CharToLong

void test_hex4CharToLong_should_equal_to_0_if_0(void) {
    long actual = hex4CharToLong(0, 0, 0, 0);

    TEST_ASSERT_EQUAL(0L, actual);
}

void test_hex2CharToLong_should_equal_to_0_if_D4B3(void) {
    long actual = hex4CharToLong(0x0D, 0x04, 0x0B, 0x03);

    TEST_ASSERT_EQUAL(54451L, actual);
}

void test_hex2CharToLong_should_equal_to_0_if_FFFF(void) {
    long actual = hex4CharToLong(0x0F, 0x0F, 0x0F, 0x0F);

    TEST_ASSERT_EQUAL(65535, actual);
}

// hex6CharToFloat

void hex6CharToLong_should_equal_to_0_if_0(void) {
    long actual = hex6CharToLong(0, 0, 0, 0, 0, 0);

    TEST_ASSERT_EQUAL_FLOAT(0, actual);
}

void hex6CharToLong_should_equal_to_1193046_if_123456(void) {
    long actual = hex6CharToLong(0x01, 0x02, 0x03, 0x04, 0x05, 0x06);

    TEST_ASSERT_EQUAL_FLOAT(1193046, actual);
}

void hex6CharToLong_should_equal_to_16777215_if_FFFFFF(void) {
    long actual = hex6CharToLong(0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F);

    TEST_ASSERT_EQUAL_FLOAT(16777215, actual);
}
