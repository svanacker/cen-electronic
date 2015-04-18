#include "../../../common/math/cenMath.h"
#include "../../../common/error/error.h"

#include "cenMathTest.h"

#include "../../../test/unity/unity.h"

// Forward Declaration

void test_absLong(void);
void test_limitLong(void);
void test_limitFloat(void);
void test_minInt(void);
void test_maxInt(void);
void test_mod2PI(void);

void cenMathTestSuite(void) {
    RUN_TEST(test_absLong);
    RUN_TEST(test_limitLong);
    RUN_TEST(test_limitFloat);
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

void test_limitLong(void) {
    long actual = limitLong(100, 200);
    TEST_ASSERT_EQUAL(100, actual);

    actual = limitLong(200, 200);
    TEST_ASSERT_EQUAL(200, actual);

    actual = limitLong(300, 200);
    TEST_ASSERT_EQUAL(200, actual);

    actual = limitLong(300, -200);
    TEST_ASSERT_EQUAL(-200, actual);

    // 0 Value
    actual = limitLong(0, 200);
    TEST_ASSERT_EQUAL(0, actual);

    actual = limitLong(-100, 200);
    TEST_ASSERT_EQUAL(-100, actual);

    actual = limitLong(-100, 200);
    TEST_ASSERT_EQUAL(-100, actual);
}

void test_limitFloat(void) {
    float actual = limitFloat(100.3f, 200.1f);
    TEST_ASSERT_EQUAL_FLOAT(100.3f, actual);

    actual = limitFloat(200.2f, 200.2f);
    TEST_ASSERT_EQUAL_FLOAT(200.2f, actual);

    actual = limitFloat(300.3f, 200.1f);
    TEST_ASSERT_EQUAL_FLOAT(200.1f, actual);

    actual = limitFloat(300.4f, -200.3f);
    TEST_ASSERT_EQUAL_FLOAT(-200.3f, actual);

    // 0 Value
    actual = limitFloat(0, 200.3f);
    TEST_ASSERT_EQUAL_FLOAT(0, actual);

    actual = limitFloat(-100.6f, 200.4f);
    TEST_ASSERT_EQUAL_FLOAT(-100.6f, actual);

    // When negative, must raise and error
    actual = limitFloat(-100.2f, -200.3f);
    TEST_ASSERT_EQUAL(LIMIT_ARGUMENT_MUST_BE_POSITIVE, getLastError());
    clearLastError();

    actual = limitFloat(-100.4f, 200.7f);
    TEST_ASSERT_EQUAL_FLOAT(-100.4f, actual);
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
