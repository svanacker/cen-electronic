/**
 * All tests for HexUtils.h
 */

void hexUtilsTestSuite(void);

// hex2CharToInt Tests

void test_hex2CharToInt_should_equal_to_0_if_0(void);

void test_hex2CharToInt_should_equal_to_197_if_C5(void);

void test_hex2CharToInt_should_equal_to_255_if_FF(void);

// hex4CharToLong Tests

void test_hex4CharToLong_should_equal_to_0_if_0(void);

void test_hex2CharToLong_should_equal_to_0_if_D4B3(void);

void test_hex2CharToLong_should_equal_to_0_if_FFFF(void);

// hex6CharToFloat

void hex6CharToFloat_should_equal_to_0_if_0(void);

void hex6CharToFloat_should_equal_to_1193046_if_123456(void);

void hex6CharToFloat_should_equal_to_16777215_if_FFFFFF(void);