#include <stdio.h>
#include <stdlib.h>

#include "../common/error/error.h"
#include "../test/unity/unity.h"

#include "../test/common/2d/2dTest.h"

#include "../test/common/io/bufferTest.h"
#include "../test/common/io/compositeOutputStreamTest.h"
#include "../test/common/io/filterTest.h"
#include "../test/common/io/ioUtilsTest.h"
#include "../test/common/io/printWriterTest.h"
#include "../test/common/io/readerTest.h"

#include "../test/common/math/bcdUtilsTest.h"
#include "../test/common/math/cenMathTest.h"
#include "../test/common/math/hexUtilsTest.h"

#include "../test/drivers/dispatchers/driverDataDispatcherListTest.h"
#include "../test/drivers/test/testDriverTest.h"

#include "../test/motion/bspline/bsplineListTest.h"

void setUp(void)
{
    clearLastError();
}

void tearDown(void)
{
}

void runAllTests(void)
{
    UnityBegin("cen");

    // RUN_TEST calls runTest
    hexUtilsTestSuite();
    bufferTestSuite();
	compositeOutputStreamTestSuite();
    filterTestSuite();
    printWriterTestSuite();
    readerTestSuite();
    ioUtilsTestSuite();
    bcdUtilsTestSuite();
    _2dTestSuite();
    cenMathTestSuite();
    driverDataDispatcherListTestSuite();
    testDriverTestTestSuite();
	bsplineListTestSuite();

    UnityEnd();
}


