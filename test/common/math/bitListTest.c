#include "bitListTest.h"

#include "../../../common/math/bitList.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../test/unity/unity.h"

#define BIT_LIST_TEST_ARRAY_LENGTH         5

/** Internal array. */
static unsigned int bitListValues[BIT_LIST_TEST_ARRAY_LENGTH];
static BitList bitList;

// Forward Declaration
void testBitList(void);

void bitListTestSuite(void) {
    RUN_TEST(testBitList);
}

void testBitList(void) {
    initBitList(&bitList, (unsigned int(*)[]) &bitListValues, BIT_LIST_TEST_ARRAY_LENGTH);
    OutputStream* outputStream = getAlwaysOutputStreamLogger();

    // Check if bit are false by default
    TEST_ASSERT_EQUAL(false, getBit(&bitList, 0));
    TEST_ASSERT_EQUAL(false, getBit(&bitList, 1));

    // set/get test

    setBit(&bitList, 35, true);
    bool actual = getBit(&bitList, 35);
    TEST_ASSERT_TRUE(actual);

    setBit(&bitList, 73, false);
    actual = getBit(&bitList, 73);
    TEST_ASSERT_FALSE(actual);

    // clearBitList
    clearBitList(&bitList, false);
    actual = getBit(&bitList, 35);
    TEST_ASSERT_FALSE(actual);
}
