#include "bsplineListTest.h"

#include "../../../common/error/error.h"

#include "../../../motion/extended/bspline.h"
#include "../../../motion/extended/bsplineList.h"

#include "../../../test/unity/unity.h"

#define TEST_BSPLINE_LIST_ARRAY_LENGTH    5
static BSplineCurveList curveListTest;
static BSplineCurve curveArrayTest[TEST_BSPLINE_LIST_ARRAY_LENGTH];

void bsplineListTestSuite(void) {
    RUN_TEST(test_init_bsplineList);
    RUN_TEST(test_read_write_bspline_list);
}

void test_init_bsplineList(void) {
    TEST_ASSERT_FALSE(isCurveListInitialized(&curveListTest));
    initCurveList(&curveListTest, (BSplineCurve(*)[]) &curveArrayTest, TEST_BSPLINE_LIST_ARRAY_LENGTH);

    TEST_ASSERT_TRUE(isCurveListInitialized(&curveListTest));
    TEST_ASSERT_TRUE(isCurveListEmpty(&curveListTest));
    TEST_ASSERT_FALSE(isCurveListFull(&curveListTest));

    TEST_ASSERT_EQUAL(0, getCurveListElementsCount(&curveListTest));
    TEST_ASSERT_EQUAL(TEST_BSPLINE_LIST_ARRAY_LENGTH - 1, getCurveListCapacity(&curveListTest));
}

void test_read_write_bspline_list(void) {
    initCurveList(&curveListTest, (BSplineCurve(*)[]) &curveArrayTest, TEST_BSPLINE_LIST_ARRAY_LENGTH);
    BSplineCurve* curve0 = getCurrentCurve(&curveListTest);

    TEST_ASSERT_EQUAL(MOTION_BSPLINE_LIST_EMPTY, getLastError());

    curve0 = getNextCurveToWrite(&curveListTest);

    curve0->p0.x = 1;
    curve0->p0.y = 2;

    curve0->p1.x = 10;
    curve0->p1.y = 20;

    curve0->p2.x = 100;
    curve0->p2.y = 200;

    curve0->p3.x = 1000;
    curve0->p3.y = 2000;

    curve0->accelerationFactor = 1;
    curve0->curveLength = 15.0;
    curve0->speedFactor = 30;

    TEST_ASSERT_EQUAL(1, getCurveListElementsCount(&curveListTest));

    // Get Current Curve must not change the current curve
    BSplineCurve* curve1 = getCurrentCurve(&curveListTest);
    TEST_ASSERT_TRUE(curve0 == curve1);

    curve1 = getNextCurveToWrite(&curveListTest);
    TEST_ASSERT_TRUE(curve0 != curve1);

    curve1->p0.x = 3;
    curve1->p0.y = 4;

    curve1->p1.x = 30;
    curve1->p1.y = 40;

    curve1->p2.x = 300;
    curve1->p2.y = 400;

    curve1->p3.x = 3000;
    curve1->p3.y = 4000;

    curve1->accelerationFactor = 2;
    curve1->curveLength = 25.0f;
    curve1->speedFactor = 40;

    TEST_ASSERT_EQUAL(2, getCurveListElementsCount(&curveListTest));
    removeCurrentCurve(&curveListTest);
    TEST_ASSERT_EQUAL(1, getCurveListElementsCount(&curveListTest));
    getNextCurveToWrite(&curveListTest);
    getNextCurveToWrite(&curveListTest);
    getNextCurveToWrite(&curveListTest);
    getNextCurveToWrite(&curveListTest);

    TEST_ASSERT_EQUAL(MOTION_BSPLINE_LIST_FULL, getLastError());
    removeCurrentCurve(&curveListTest);
    removeCurrentCurve(&curveListTest);
    removeCurrentCurve(&curveListTest);
    getNextCurveToWrite(&curveListTest);

    TEST_ASSERT_EQUAL(2, getCurveListElementsCount(&curveListTest));
}
