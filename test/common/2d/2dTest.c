#include "2dTest.h"

#include "../../../common/2d/2d.h"

#include "../../../test/unity/unity.h"

#define PI                3.141592653f
#define PI_DIVIDE_2        1.570796326f

void _2dTestSuite(void) {
    RUN_TEST(test_distanceBetweenPoints);
    RUN_TEST(test_angleOfVector);
    RUN_TEST(test_scale);
    RUN_TEST(test_rotate);
}

void test_distanceBetweenPoints(void) {
    Point p0;
    Point p1;
    p0.x = 1;
    p0.y = 2;
    p1.x = 2;
    p1.y = 3;
    float actual = distanceBetweenPoints(&p0, &p1);

    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, 1.414213562f, actual);

    p0.x = 5;
    p0.y = 8;
    p1.x = -3;
    p1.y = -1;

    actual = distanceBetweenPoints(&p0, &p1);

    TEST_ASSERT_EQUAL_FLOAT(12.04159457f, actual);
}

void test_angleOfVector(void) {
    Point p0;
    Point p1;
    p0.x = 0;
    p0.y = 0;
    p1.x = 0;
    p1.y = 0;
    float actual = angleOfVector(&p0, &p1);
    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, 0.0f, actual);

    p0.x = 0;
    p0.y = 0;
    p1.x = 1;
    p1.y = 0;
    actual = angleOfVector(&p0, &p1);
    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, 0.0f, actual);

    p0.x = 0;
    p0.y = 0;
    p1.x = -1;
    p1.y = 0;
    actual = angleOfVector(&p0, &p1);
    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, PI, actual);

    p0.x = 0;
    p0.y = 0;
    p1.x = 0;
    p1.y = 1;
    actual = angleOfVector(&p0, &p1);
    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, PI / 2, actual);

    p0.x = 1;
    p0.y = 2;
    p1.x = 4;
    p1.y = 5;
    actual = angleOfVector(&p0, &p1);
    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, PI / 4, actual);

    p0.x = 4;
    p0.y = 5;
    p1.x = 1;
    p1.y = 2;

    actual = angleOfVector(&p0, &p1);
    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, -3 * PI / 4, actual);
}

void test_scale(void) {
    // TODO : Fixed This !!!
    /*
    Point p0;
    p0.x = 0;
    p0.y = 0;
    scale(&p0, 0.0f);
    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, 0.0f, p0.x);
    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, 0.0f, p0.y);

    p0.x = 1;
    p0.y = 2;
    scale(&p0, 5.0f);
    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION,5.0f, p0.x);
    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION,10.0f, p0.y);
    */
}

void test_rotate(void) {
    Point p0;
    rotate(&p0, PI_DIVIDE_2, 2.0, 0.0);
    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, 0.0, p0.x);
    TEST_ASSERT_FLOAT_WITHIN(UNITY_FLOAT_PRECISION, 2.0, p0.y);
}
