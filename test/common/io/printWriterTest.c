#include "printWriterTest.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/error/error.h"

#include "../../../test/unity/unity.h"

#define TEST_BUFFER_SIZE 10

static Buffer bufferTest;
static char bufferArrayTest[TEST_BUFFER_SIZE];

// append

void test_append_simple(void) {
	initBuffer(&bufferTest, &bufferArrayTest, TEST_BUFFER_SIZE, "nameTest", "typeTest");
	OutputStream* outputStream = getOutputStream(&bufferTest);
	
	append(outputStream, 'a');

	char actual = bufferReadChar(&bufferTest);
	TEST_ASSERT_EQUAL('a', actual);
}

void test_append_repeat(void) {
	initBuffer(&bufferTest, &bufferArrayTest, TEST_BUFFER_SIZE, "nameTest", "typeTest");
	OutputStream* outputStream = getOutputStream(&bufferTest);

	int i;
	for (i = 0; i < 60; i++) {
		append(outputStream, 'A' + i);

		char actual = bufferReadChar(&bufferTest);
		TEST_ASSERT_EQUAL('A' + i, actual);
	}
}
