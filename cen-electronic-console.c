#include <stdio.h>
#include <stdlib.h>

#include "common/error/error.h"
#include "test/unity/unity.h"

#include "test/common/io/bufferTest.h"
#include "test/common/io/printWriterTest.h"
#include "test/common/io/readerTest.h"

#include "test/common/math/hexUtilsTest.h"

void setUp(void)
{
	clearLastError();
}

void tearDown(void)
{
}

void hexUtilsTests() {
	RUN_TEST(test_hex2CharToInt_should_equal_to_0_if_0);
	RUN_TEST(test_hex2CharToInt_should_equal_to_197_if_C5);
	RUN_TEST(test_hex2CharToInt_should_equal_to_255_if_FF);

	RUN_TEST(test_hex4CharToLong_should_equal_to_0_if_0);
	RUN_TEST(test_hex2CharToLong_should_equal_to_0_if_D4B3);
	RUN_TEST(test_hex2CharToLong_should_equal_to_0_if_FFFF);

	RUN_TEST(hex6CharToFloat_should_equal_to_0_if_0);
	RUN_TEST(hex6CharToFloat_should_equal_to_1193046_if_123456);
	RUN_TEST(hex6CharToFloat_should_equal_to_16777215_if_FFFFFF);
}

void bufferTests() {


	RUN_TEST(test_initBuffer_with_null_buffer_should_throw_buffer_null_error);
	RUN_TEST(test_initBuffer_should_be_right_initialized_and_empty_and_not_full);
	RUN_TEST(test_initBuffer_should_throw_error_when_empty_and_reading_char);

	RUN_TEST(test_bufferWriteChar);
	RUN_TEST(test_bufferWriteChar_too_much_writes);
	RUN_TEST(test_bufferWriteChar_and_read_several_times);

	RUN_TEST(test_isBufferEqualsToString);

	RUN_TEST(test_bufferGetCharAtIndex);

	RUN_TEST(test_getBufferCapacity);

	RUN_TEST(test_clearBuffer);

	RUN_TEST(test_deepClearBuffer);

	RUN_TEST(test_getOutputStream);
	RUN_TEST(test_getOutputStream_if_buffer_null);
	RUN_TEST(test_getInputStream);
	RUN_TEST(test_getInputStream_if_buffer_null);
}

void printWriterTests() {
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

void readerTests(void) {
	RUN_TEST(test_readFilteredChar);
}

int main(int argc, char *argv[])
{
	UnityBegin("cen-electronic-console");

	// RUN_TEST calls runTest

	hexUtilsTests();
	bufferTests();
	printWriterTests();
	readerTests();

	UnityEnd();

	getchar();
	return EXIT_SUCCESS;
}


