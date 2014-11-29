#include "../../../common/math/cenMath.h"

#include "cenMathTest.h"

#include "../../../test/unity/unity.h"

void cenMathTestSuite(void) {
	RUN_TEST(test_absLong);
	RUN_TEST(test_limit);
}

void test_absLong(void) {
	long actual = absLong(-1);
	TEST_ASSERT_EQUAL(1, actual);

	actual = absLong(0);
	TEST_ASSERT_EQUAL(0, actual);

	actual = absLong(254);
	TEST_ASSERT_EQUAL(254, actual);

	actual = absLong(-65536);
	TEST_ASSERT_EQUAL(65536, actual);

	actual = absLong(2147483647);
	TEST_ASSERT_EQUAL(2147483647, actual);

	actual = absLong(-2147483647);
	TEST_ASSERT_EQUAL(2147483647, actual);
}

void test_limit(void) {
	long actual = limit(100, 200);
	TEST_ASSERT_EQUAL(100, actual);

	actual = limit(200, 200);
	TEST_ASSERT_EQUAL(200, actual);

	actual = limit(300, 200);
	TEST_ASSERT_EQUAL(200, actual);

	actual = limit(300, -200);
	TEST_ASSERT_EQUAL(-200, actual);

	// 0 Value
	actual = limit(0, 200);
	TEST_ASSERT_EQUAL(0, actual);

	actual = limit(-100, 200);
	TEST_ASSERT_EQUAL(-100, actual);

	// TODO : Clarify the usage and Fix Test
	actual = limit(-100, -200);
	TEST_ASSERT_EQUAL(-100, actual);

	actual = limit(-100, 200);
	TEST_ASSERT_EQUAL(-100, actual);
}