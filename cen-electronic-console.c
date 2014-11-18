#include <stdio.h>
#include <stdlib.h>

#include "common/error/error.h"
#include "test/unity/unity.h"
#include "test/common/io/bufferTest.h"
#include "test/common/math/hexUtilsTest.h"

void setUp(void)
{
	clearLastError();
}

void tearDown(void)
{
}

int main(int argc, char *argv[])
{
	UnityBegin("cen-electronic-console");

	// RUN_TEST calls runTest
	RUN_TEST(test_hex2CharToInt_should_equal_to_0_if_0);
	RUN_TEST(test_hex2CharToInt_should_equal_to_197_if_C5);
	RUN_TEST(test_hex2CharToInt_should_equal_to_255_if_FF);

	RUN_TEST(test_hex4CharToLong_should_equal_to_0_if_0);
	RUN_TEST(test_hex2CharToLong_should_equal_to_0_if_D4B3);
	RUN_TEST(test_hex2CharToLong_should_equal_to_0_if_FFFF);

	RUN_TEST(hex6CharToFloat_should_equal_to_0_if_0);
	RUN_TEST(hex6CharToFloat_should_equal_to_1193046_if_123456);
	RUN_TEST(hex6CharToFloat_should_equal_to_16777215_if_FFFFFF);

	RUN_TEST(test_initBuffer_with_null_buffer_should_throw_buffer_null_error);
	RUN_TEST(test_initBuffer_should_be_right_initialized_and_empty_and_not_full);
	RUN_TEST(test_initBuffer_should_throw_error_when_empty_and_reading_char);

	RUN_TEST(test_bufferWriteChar);
	RUN_TEST(test_bufferWriteChar_too_much_writes);
	RUN_TEST(test_bufferWriteChar_and_read_several_times);

	RUN_TEST(test_bufferGetCharAtIndex);

	RUN_TEST(test_getBufferCapacity);

	RUN_TEST(test_clearBuffer);

	RUN_TEST(test_deepClearBuffer);

	UnityEnd();

	getchar();
	return EXIT_SUCCESS;
}


