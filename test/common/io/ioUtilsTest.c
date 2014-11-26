#include "ioUtilsTest.h"

#include <stdbool.h>

#include "../../../common/io/buffer.h"
#include "../../../common/io/ioUtils.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/outputStream.h"

#include "../../../test/unity/unity.h"

#define TEST_BUFFER_SIZE 20

static Buffer sourceBufferTest;
static char sourceBufferArrayTest[TEST_BUFFER_SIZE];
static OutputStream* sourceOutputStream;
static InputStream* sourceInputStream;

static Buffer targetBufferTest;
static char targetBufferArrayTest[TEST_BUFFER_SIZE];
static OutputStream* targetOutputStream;

void ioUtilsTestSuite(void) {
	RUN_TEST(test_copyInputToOutputStream);
}

void initBufferForIoUtilsTest(void) {
	// source
	initBuffer(&sourceBufferTest, (char(*)[]) &sourceBufferArrayTest, TEST_BUFFER_SIZE, "ioUtilsTest", "ioUtilsTestType");
	sourceOutputStream = getOutputStream(&sourceBufferTest);
	sourceInputStream = getInputStream(&sourceBufferTest);

	// target
	initBuffer(&targetBufferTest, (char(*)[]) &targetBufferArrayTest, TEST_BUFFER_SIZE, "ioUtilsTest", "ioUtilsTestType");
	targetOutputStream = getOutputStream(&targetBufferTest);
}


void test_copyInputToOutputStream(void) {
	initBufferForIoUtilsTest();

	append(sourceOutputStream, 'c');

	copyInputToOutputStream(sourceInputStream, targetOutputStream, NULL, 1);

	char targetChar = bufferReadChar(&targetBufferTest);
	TEST_ASSERT_EQUAL('c', targetChar);
}