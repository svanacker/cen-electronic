#include "../../../common/math/cenMath.h"

#include "cenMathTest.h"

#include "../../../test/unity/unity.h"

void cenMathTestSuite(void) {
	RUN_TEST(test_absLong);
	RUN_TEST(test_limit);
	RUN_TEST(test_minInt);
	RUN_TEST(test_maxInt);
	RUN_TEST(test_mod2PI);
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
	TEST_IGNORE_MESSAGE("TODO : TO FIX");

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

void test_minInt(void) {
	int actual = minInt(0, 0);
	TEST_ASSERT_EQUAL(0, actual);

	actual = minInt(0, 25000);
	TEST_ASSERT_EQUAL(0, actual);

	actual = minInt(25000, 0);
	TEST_ASSERT_EQUAL(0, actual);

	actual = minInt(-25000, 0);
	TEST_ASSERT_EQUAL(-25000, actual);

	actual = minInt(-25000, 100);
	TEST_ASSERT_EQUAL(-25000, actual);

	actual = minInt(-25000, 30000);
	TEST_ASSERT_EQUAL(-25000, actual);

	actual = minInt(-25000, 22000);
	TEST_ASSERT_EQUAL(-25000, actual);

	actual = minInt(10, 30000);
	TEST_ASSERT_EQUAL(10, actual);
}

void test_maxInt(void) {
	int actual = maxInt(0, 0);
	TEST_ASSERT_EQUAL(0, actual);

	actual = maxInt(0, 25000);
	TEST_ASSERT_EQUAL(25000, actual);

	actual = maxInt(25000, 0);
	TEST_ASSERT_EQUAL(25000, actual);

	actual = maxInt(-25000, 0);
	TEST_ASSERT_EQUAL(0, actual);

	actual = maxInt(-25000, 100);
	TEST_ASSERT_EQUAL(100, actual);

	actual = maxInt(-25000, 30000);
	TEST_ASSERT_EQUAL(30000, actual);

	actual = maxInt(10, 30000);
	TEST_ASSERT_EQUAL(30000, actual);
}

void test_mod2PI(void) {
	float actual = mod2PI(0.0f);
	TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, 0.0f, actual);

	actual = mod2PI(PI);
	TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, PI, actual);

	actual = mod2PI(PI - 0.0001f);
	TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, PI - 0.0001F, actual);

	actual = mod2PI(PI + 0.0001f);
	TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, -PI + 0.0001F, actual);

	actual = mod2PI(PI + 2.0f);
	TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, -PI + 2.0f, actual);

	actual = mod2PI(5 * PI + 1.0f);
	TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, -PI + 1.0f, actual);

	actual = mod2PI(5 * PI - 1.0f);
	TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, PI - 1.0f, actual);

	actual = mod2PI(-PI - 2.0f);
	TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, +PI - 2.0f, actual);

	actual = mod2PI(-5 * PI + 1.0f);
	TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, -PI + 1.0f, actual);

	actual = mod2PI(-PI - 0.0001f);
	TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, PI - 0.0001F, actual);

	actual = mod2PI(-PI + 0.0001f);
	TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, -PI + 0.0001F, actual);
}
