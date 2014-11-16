#include "../../../common/math/hexUtils.h"
#include "../../../test/unity/unity.h"

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

void hex6CharToFloat_should_equal_to_0_if_0(void) {
	float actual = hex6CharToFloat(0, 0, 0, 0, 0, 0);

	TEST_ASSERT_EQUAL_FLOAT(0.0F, actual);
}

void hex6CharToFloat_should_equal_to_1193046_if_123456(void) {
	float actual = hex6CharToFloat(0x01, 0x02, 0x03, 0x04, 0x05, 0x06);

	TEST_ASSERT_EQUAL_FLOAT(1193046.0F, actual);
}

void hex6CharToFloat_should_equal_to_16777215_if_FFFFFF(void) {
	float actual = hex6CharToFloat(0x0F, 0x0F, 0x0F, 0x0F, 0x0F, 0x0F);

	TEST_ASSERT_EQUAL_FLOAT(16777215.0F, actual);
}
