#include "memoryEepromTest.h"

#include <stdlib.h>

#include "../../../common/eeprom/eeprom.h"
#include "../../../common/eeprom/memoryEeprom.h"
#include "../../../common/error/error.h"

#include "../../../test/unity/unity.h"

#define MEMORY_EEPROM_TEST      10

static Eeprom eepromMemoryTest;
static char memoryArrayTest[MEMORY_EEPROM_TEST];

// forward declaration
void test_memoryEeprom(void);

void memoryEepromTestSuite(void) {
    RUN_TEST(test_memoryEeprom);
}

void test_memoryEeprom(void) {
    initEepromMemory(&eepromMemoryTest, (char(*)[]) memoryArrayTest, MEMORY_EEPROM_TEST);
    memoryArrayTest[5] = 0x56;
    memoryArrayTest[6] = 0x78;

    // write test
    eepromWriteInt(&eepromMemoryTest, 2, 0x1234);

    char highValue = eepromMemoryTest.eepromReadChar(&eepromMemoryTest, 2);
    char lowValue = eepromMemoryTest.eepromReadChar(&eepromMemoryTest, 3);
    TEST_ASSERT_EQUAL(0x12, highValue);
    TEST_ASSERT_EQUAL(0x34, lowValue);

    // read test
    highValue = eepromMemoryTest.eepromReadChar(&eepromMemoryTest, 5);
    lowValue= eepromMemoryTest.eepromReadChar(&eepromMemoryTest, 6);

    TEST_ASSERT_EQUAL(0x56, highValue);
    TEST_ASSERT_EQUAL(0x78, lowValue);
}