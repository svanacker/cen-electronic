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

#include "../test/common/eeprom/memoryEepromTest.h"

#include "../test/common/math/bcdUtilsTest.h"
#include "../test/common/math/bitListTest.h"
#include "../test/common/math/cenMathTest.h"
#include "../test/common/math/hexUtilsTest.h"

#include "../test/drivers/dispatchers/driverDataDispatcherListTest.h"
#include "../test/drivers/test/testDriverTest.h"

#include "../test/motion/bspline/bsplineListTest.h"
#include "../test/navigation/locationListTest.h"
#include "../test/navigation/pathListTest.h"
#include "../test/navigation/navigationTest.h"

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

    // 2d    
    _2dTestSuite();

    // eeprom
    memoryEepromTestSuite();

    // math
    hexUtilsTestSuite();
    bitListTestSuite();
    bcdUtilsTestSuite();
    cenMathTestSuite();

    // io
    bufferTestSuite();
    compositeOutputStreamTestSuite();
    filterTestSuite();
    printWriterTestSuite();
    readerTestSuite();
    ioUtilsTestSuite();
    
    // Drivers
    driverDataDispatcherListTestSuite();
    testDriverTestTestSuite();

    // motion->extended
    bsplineListTestSuite();

    // navigation
    locationListTestSuite();
    pathListTestSuite();
    navigationTestSuite();

    UnityEnd();
}


