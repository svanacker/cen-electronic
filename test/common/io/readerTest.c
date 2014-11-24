#include "readerTest.h"

#include "../../../common/error/error.h"

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

void test_readFilteredChar(void) {
	initBufferForReaderTest();

	appendString(outputStream, "HELL\0");

	char value = readFilteredChar(inputStream);
	TEST_ASSERT_EQUAL('H', value);
	TEST_ASSERT_EQUAL(0, getLastError());

	// E must return 14 and not 69 because [0..F] is transform into the corresponding value
	value = readFilteredChar(inputStream);
	TEST_ASSERT_EQUAL(14, value);
	TEST_ASSERT_EQUAL(0, getLastError());

	value = readFilteredChar(inputStream);
	TEST_ASSERT_EQUAL('L', value);
	TEST_ASSERT_EQUAL(0, getLastError());

	value = readFilteredChar(inputStream);
	TEST_ASSERT_EQUAL('L', value);
	TEST_ASSERT_EQUAL(0, getLastError());

	value = readFilteredChar(inputStream);
	TEST_ASSERT_EQUAL(FILTERED_RESULT, value);
	TEST_ASSERT_EQUAL(IO_READER_READ_FILTERED_CHAR, getLastError());
}

void test_readBinaryChar(void) {
	initBufferForReaderTest();

	appendString(outputStream, "\1Az");

	char value = readBinaryChar(inputStream);
	TEST_ASSERT_EQUAL('\1', value);
	// Don't produce any error ! We read it as is !
	TEST_ASSERT_EQUAL(0, getLastError());

	clearLastError();
	value = readBinaryChar(inputStream);
	TEST_ASSERT_EQUAL('A', value);
	TEST_ASSERT_EQUAL(0, getLastError());

	clearLastError();
	value = readBinaryChar(inputStream);
	TEST_ASSERT_EQUAL('z', value);
	TEST_ASSERT_EQUAL(0, getLastError());
}

void test_readBinaryWord(void) {
	initBufferForReaderTest();

	appendString(outputStream, "Fz");
	int value = readBinaryWord(inputStream);
	// 'z' (122) + 'F'(70) * 256 => 18042
	TEST_ASSERT_EQUAL(18042, value);
}

void test_readHex(void) {
	initBufferForReaderTest();

	appendString(outputStream, "\1F");

	char value = readHex(inputStream);
	TEST_ASSERT_EQUAL(FILTERED_RESULT, value);
	TEST_ASSERT_EQUAL(IO_READER_READ_FILTERED_CHAR, getLastError());
	clearLastError();

	value = readHex(inputStream);
	TEST_ASSERT_EQUAL(15, value);
	TEST_ASSERT_EQUAL(0, getLastError());
}

void test_readHex2(void) {
	initBufferForReaderTest();

	appendString(outputStream, "B5FF10");

	// B5
	int value = readHex2(inputStream);
	TEST_ASSERT_EQUAL(181, value);
	TEST_ASSERT_EQUAL(0, getLastError());

	// FF
	value = readHex2(inputStream);
	TEST_ASSERT_EQUAL(255, value);
	TEST_ASSERT_EQUAL(0, getLastError());

	// 10
	value = readHex2(inputStream);
	TEST_ASSERT_EQUAL(16, value);
	TEST_ASSERT_EQUAL(0, getLastError());
}