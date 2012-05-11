#include "bitListTest.h"

#include "../../../common/math/bitList.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

/** Internal array. */
static unsigned int bitListValues[BIT_LIST_TEST_ARRAY_LENGTH];
static BitList bitList;

void testBitList() {
	initBitList(&bitList, &bitListValues, BIT_LIST_TEST_ARRAY_LENGTH);
	OutputStream* outputStream = getOutputStreamLogger(ALWAYS);

	printBitList(outputStream, &bitList);

	setBit(&bitList, 75, TRUE);
	printBitList(outputStream, &bitList);

	setBit(&bitList, 73, FALSE);
	printBitList(outputStream, &bitList);
}
