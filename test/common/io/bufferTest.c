#include <stdlib.h>

#include "../../../common/io/buffer.h"
#include "../../../common/error/error.h"

#include "../../../test/unity/unity.h"

#define TEST_BUFFER_SIZE 100
static char bufferArrayTest[TEST_BUFFER_SIZE];

void test_initBuffer_with_null_buffer_should_throw_buffer_null_error() {
	initBuffer(NULL, &bufferArrayTest, TEST_BUFFER_SIZE, "nameTest", "typeTest");

	int actual = getLastError();

	TEST_ASSERT_EQUAL(IO_BUFFER_NULL, actual);
}