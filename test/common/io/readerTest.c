#include "readerTest.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../test/unity/unity.h"

#define TEST_BUFFER_SIZE 20

static Buffer bufferTest;
static char bufferArrayTest[TEST_BUFFER_SIZE];
static OutputStream* outputStream;
static InputStream* inputStream;

void initBufferForReaderTest(void) {
	initBuffer(&bufferTest, (char(*)[]) &bufferArrayTest, TEST_BUFFER_SIZE, "printWriter", "printWriterTestType");
	outputStream = getOutputStream(&bufferTest);
	inputStream = getInputStream(&bufferTest);
}

void test_readFilteredChar() {
	initBufferForReaderTest();

	appendString(outputStream, "HELLO World");

	char value = readFilteredChar(inputStream);
	TEST_ASSERT_EQUAL('H', value);

	// E must return 14 and not 69 because [0..F] is transform into the corresponding value
	value = readFilteredChar(inputStream);
	TEST_ASSERT_EQUAL(14, value);

	value = readFilteredChar(inputStream);
	TEST_ASSERT_EQUAL('L', value);
}
