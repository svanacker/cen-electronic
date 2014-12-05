#include "printWriterTest.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/pc/consoleOutputStream.h"
#include "../../../common/error/error.h"


#include "../../../test/unity/unity.h"

#define TEST_BUFFER_SIZE 20

static Buffer bufferTest;
static char bufferArrayTest[TEST_BUFFER_SIZE];
static OutputStream* outputStream;

static Buffer bufferTest2;
static char bufferArrayTest2[TEST_BUFFER_SIZE];

void printWriterTestSuite(void) {
	RUN_TEST(test_append_simple);
	RUN_TEST(test_append_repeat);

	RUN_TEST(test_appendBool);

	RUN_TEST(test_appendSeparator);

	RUN_TEST(test_appendString);

	RUN_TEST(test_printBuffer);

	RUN_TEST(test_appendHex);
	RUN_TEST(test_appendHex2);
	RUN_TEST(test_appendHex3);
	RUN_TEST(test_appendHex4);
	RUN_TEST(test_appendHex5);
	RUN_TEST(test_appendHex6);
	RUN_TEST(test_appendHex8);

	RUN_TEST(test_appendDec_simple);
	RUN_TEST(test_appendDec_negative_value);

	RUN_TEST(test_appendDecf_positive_value1);
	RUN_TEST(test_appendDecf_positive_value2);
	RUN_TEST(test_appendDecf_positive_value3);
	RUN_TEST(test_appendDecf_positive_value4);
	RUN_TEST(test_appendDecf_positive_value5);
	RUN_TEST(test_appendDecf_negative_value1);
	RUN_TEST(test_appendDecf_negative_value2);
}

void initBufferForPrintWriterTest(void) {
	initBuffer(&bufferTest, (char(*)[]) &bufferArrayTest, TEST_BUFFER_SIZE, "printWriter", "printWriterTestType");
	outputStream = getOutputStream(&bufferTest);
}

// append

void test_append_simple(void) {
	initBufferForPrintWriterTest();
	
	append(outputStream, 'a');

	char actual = bufferReadChar(&bufferTest);
	TEST_ASSERT_EQUAL('a', actual);
}

void test_append_repeat(void) {
	initBufferForPrintWriterTest();

	int i;
	for (i = 0; i < 60; i++) {
		append(outputStream, 'A' + i);

		char actual = bufferReadChar(&bufferTest);
		TEST_ASSERT_EQUAL('A' + i, actual);
	}
}

void test_appendBool(void) {
	initBufferForPrintWriterTest();

	appendBool(outputStream, true);
	appendBool(outputStream, false);

	char trueReadChar = bufferReadChar(&bufferTest);
	TEST_ASSERT_EQUAL('1', trueReadChar);

	char falseReadChar = bufferReadChar(&bufferTest);
	TEST_ASSERT_EQUAL('0', falseReadChar);
}

void test_appendSeparator(void) {
	initBufferForPrintWriterTest();

	appendSeparator(outputStream);

	char separatorChar = bufferReadChar(&bufferTest);
	TEST_ASSERT_EQUAL('-', separatorChar);
}

void test_appendString(void) {
	initBufferForPrintWriterTest();

	appendString(outputStream, "HELLO");

	bool actual = isBufferEqualsToString(&bufferTest, "HELLO");
	TEST_ASSERT_TRUE(actual);
}

// printBuffer

void test_printBuffer(void) {
	// Buffer 1
	initBuffer(&bufferTest, (char(*)[]) &bufferArrayTest, TEST_BUFFER_SIZE, "nameTest", "typeTest");
	OutputStream* outputStream1 = getOutputStream(&bufferTest);
	appendString(outputStream1, "HELLO");

	// Buffer 2
	initBuffer(&bufferTest2, (char(*)[]) &bufferArrayTest2, TEST_BUFFER_SIZE, "nameTest2", "typeTest2");
	OutputStream* outputStream2 = getOutputStream(&bufferTest2);

	// Copy from Buffer 1 to Buffer 2
	printBuffer(outputStream2, &bufferTest);

	bool actual = isBufferEqualsToString(&bufferTest2, "HELLO");
	TEST_ASSERT_TRUE(actual);
}

// appendHex

void test_appendHex(void) {
	initBufferForPrintWriterTest();

	bool actual = appendHex(outputStream, 0);
	TEST_ASSERT_TRUE(actual);
	TEST_ASSERT_EQUAL('0', bufferReadChar(&bufferTest));

	actual = appendHex(outputStream, 8);
	TEST_ASSERT_TRUE(actual);
	TEST_ASSERT_EQUAL('8', bufferReadChar(&bufferTest));

	actual = appendHex(outputStream, 10);
	TEST_ASSERT_TRUE(actual);
	TEST_ASSERT_EQUAL('A', bufferReadChar(&bufferTest));

	actual = appendHex(outputStream, 15);
	TEST_ASSERT_TRUE(actual);
	TEST_ASSERT_EQUAL('F', bufferReadChar(&bufferTest));

	// Must not append if > 15
	actual = appendHex(outputStream, 16);
	TEST_ASSERT_FALSE(actual);
	TEST_ASSERT_TRUE(isBufferEmpty(&bufferTest));
	TEST_ASSERT_EQUAL(PRINT_WRITER_NOT_HEX_VALUE, getLastError());
	clearLastError();

	actual = appendHex(outputStream, 120);
	TEST_ASSERT_FALSE(actual);
	TEST_ASSERT_TRUE(isBufferEmpty(&bufferTest));
	TEST_ASSERT_EQUAL(PRINT_WRITER_NOT_HEX_VALUE, getLastError());
}

// appendHex2

void test_appendHex2(void) {
	initBufferForPrintWriterTest();

	appendHex2(outputStream, 0);
	bool actual = isBufferEqualsToString(&bufferTest, "00");
	TEST_ASSERT_TRUE(actual);

	clearBuffer(&bufferTest);

	appendHex2(outputStream, 0x42);
	actual = isBufferEqualsToString(&bufferTest, "42");
	TEST_ASSERT_TRUE(actual);
	clearBuffer(&bufferTest);

	appendHex2(outputStream, 0xFF);
	actual = isBufferEqualsToString(&bufferTest, "FF");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

// appendHex3

void test_appendHex3(void) {
	initBufferForPrintWriterTest();

	appendHex3(outputStream, 0x01A3);
	bool actual = isBufferEqualsToString(&bufferTest, "1A3");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

// appendHex4

void test_appendHex4(void) {
	initBufferForPrintWriterTest();

	appendHex4(outputStream, 0x1A3B);
	bool actual = isBufferEqualsToString(&bufferTest, "1A3B");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

// appendHex5

void test_appendHex5(void) {
	initBufferForPrintWriterTest();

	appendHex5(outputStream, 0x000C23BF);
	bool actual = isBufferEqualsToString(&bufferTest, "C23BF");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

// appendHex6

void test_appendHex6(void) {
	initBufferForPrintWriterTest();

	appendHex6(outputStream, 0x00A1F3B8);
	bool actual = isBufferEqualsToString(&bufferTest, "A1F3B8");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

// appendHex8

void test_appendHex8(void) {
	initBufferForPrintWriterTest();

	appendHex8(outputStream, 0x00A1F3B807);
	bool actual = isBufferEqualsToString(&bufferTest, "A1F3B807");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

// appendDec

void test_appendDec_simple(void) {
	initBufferForPrintWriterTest();

	appendDec(outputStream, 1234);
	bool actual = isBufferEqualsToString(&bufferTest, "1234");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

void test_appendDec_negative_value(void) {
	initBufferForPrintWriterTest();

	appendDec(outputStream, -1234);
	bool actual = isBufferEqualsToString(&bufferTest, "-1234");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

void test_appendDecf_positive_value1(void) {
	initBufferForPrintWriterTest();

	int value = appendDecf(outputStream, 1234.56789F);

	bool actual = isBufferEqualsToString(&bufferTest, "1234.568");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

void test_appendDecf_positive_value2(void) {
	initBufferForPrintWriterTest();

	appendDecf(outputStream, 1234.000F);
	bool actual = isBufferEqualsToString(&bufferTest, "1234.000");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

void test_appendDecf_positive_value3(void) {
	initBufferForPrintWriterTest();

	appendDecf(outputStream, 1234.002F);

	/*
	OutputStream consoleOutputStream;
	initConsoleOutputStream(&consoleOutputStream);
	printDebugBuffer(&consoleOutputStream, &bufferTest);
	*/

	bool actual = isBufferEqualsToString(&bufferTest, "1234.002");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

void test_appendDecf_positive_value4(void) {
	initBufferForPrintWriterTest();

	appendDecf(outputStream, 1234.020F);
	bool actual = isBufferEqualsToString(&bufferTest, "1234.020");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

void test_appendDecf_positive_value5(void) {
	initBufferForPrintWriterTest();

	appendDecf(outputStream, 1234.300F);
	bool actual = isBufferEqualsToString(&bufferTest, "1234.300");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

void test_appendDecf_negative_value1(void) {
	initBufferForPrintWriterTest();

	appendDecf(outputStream, -1234.56789F);
	bool actual = isBufferEqualsToString(&bufferTest, "-1234.568");
	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}

void test_appendDecf_negative_value2(void) {
	initBufferForPrintWriterTest();

	appendDecf(outputStream, -1234.0F);
	bool actual = isBufferEqualsToString(&bufferTest, "-1234.000");

	// OutputStream consoleOutputStream;
	// initConsoleOutputStream(&consoleOutputStream);
	// printDebugBuffer(&consoleOutputStream, &bufferTest);

	TEST_ASSERT_TRUE(actual);

	TEST_ASSERT_FALSE(isThereAnyError());
}
