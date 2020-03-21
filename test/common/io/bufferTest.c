#include <stdlib.h>

#include "bufferTest.h"

#include "../../../common/io/buffer.h"
#include "../../../common/error/error.h"

#include "../../../test/unity/unity.h"

#define TEST_BUFFER_SIZE 100

static Buffer bufferTest;
static char bufferArrayTest[TEST_BUFFER_SIZE];

void bufferTestSuite(void) {
    RUN_TEST(test_initBuffer_with_null_buffer_should_throw_buffer_null_error);
    RUN_TEST(test_initBuffer_should_be_right_initialized_and_empty_and_not_full);
    RUN_TEST(test_initBuffer_should_throw_error_when_empty_and_reading_char);

    RUN_TEST(test_bufferWriteChar);
    RUN_TEST(test_bufferWriteChar_too_much_writes);
    RUN_TEST(test_bufferWriteChar_and_read_several_times);

    RUN_TEST(test_isBufferEqualsToString);

    RUN_TEST(test_bufferWriteCharAtIndex);
    RUN_TEST(test_bufferGetCharAtIndex);

    RUN_TEST(test_getBufferCapacity);

    RUN_TEST(test_clearBuffer);

    RUN_TEST(test_deepClearBuffer);

    RUN_TEST(test_getOutputStream);
    RUN_TEST(test_getOutputStream_if_buffer_null);
    RUN_TEST(test_getInputStream);
    RUN_TEST(test_getInputStream_if_buffer_null);
}

void initNullBufferForTest(void) {
    initBuffer(NULL, (char(*)[]) & bufferArrayTest, TEST_BUFFER_SIZE, "bufferTest", "bufferTestType");
}

void initBufferForTest(void) {
    initBuffer(&bufferTest, (char(*)[]) & bufferArrayTest, TEST_BUFFER_SIZE, "bufferTest", "bufferTestType");
}

// initBuffer

void test_initBuffer_with_null_buffer_should_throw_buffer_null_error(void) {
    initNullBufferForTest();

    int actual = getLastError();
    TEST_ASSERT_EQUAL(IO_BUFFER_NULL, actual);
    clearLastError();

    isBufferInitialized(NULL);
    actual = getLastError();
    TEST_ASSERT_EQUAL(IO_BUFFER_NULL, actual);
    clearLastError();

    isBufferFull(NULL);
    actual = getLastError();
    TEST_ASSERT_EQUAL(IO_BUFFER_NULL, actual);
}

void test_initBuffer_should_be_right_initialized_and_empty_and_not_full(void) {
    initBufferForTest();

    bool initialized = isBufferInitialized(&bufferTest);
    TEST_ASSERT_TRUE(initialized);

    bool empty = isBufferEmpty(&bufferTest);
    TEST_ASSERT_TRUE(empty);
}

void test_initBuffer_should_throw_error_when_empty_and_reading_char(void) {
    initBufferForTest();

    char actual = bufferReadChar(&bufferTest);
    TEST_ASSERT_EQUAL(0, actual);

    int lastError = getLastError();
    TEST_ASSERT_EQUAL(IO_BUFFER_EMPTY, lastError);

    actual = bufferGetCharAtIndex(&bufferTest, 0);
    lastError = getLastError();
    TEST_ASSERT_EQUAL(IO_BUFFER_NOT_ENOUGH_DATA, lastError);
}

// isBufferEqualsToString

void test_isBufferEqualsToString(void) {
    initBufferForTest();

    // buffer is empty => Can not be equals to 0
    bool actual = isBufferEqualsToString(&bufferTest, "HELLO");
    TEST_ASSERT_FALSE(actual);

    // Second test, just write a char
    bufferWriteChar(&bufferTest, 'H');
    actual = isBufferEqualsToString(&bufferTest, "H");
    TEST_ASSERT_TRUE(actual);

    actual = isBufferEqualsToString(&bufferTest, "HELLO");
    TEST_ASSERT_FALSE(actual);

    bufferWriteChar(&bufferTest, 'E');
    bufferWriteChar(&bufferTest, 'L');
    bufferWriteChar(&bufferTest, 'L');
    bufferWriteChar(&bufferTest, 'O');

    actual = isBufferEqualsToString(&bufferTest, "HELLO");
    TEST_ASSERT_TRUE(actual);

    bufferWriteChar(&bufferTest, ' ');
    bufferWriteChar(&bufferTest, 'W');
    bufferWriteChar(&bufferTest, 'O');
    bufferWriteChar(&bufferTest, 'R');
    bufferWriteChar(&bufferTest, 'L');
    bufferWriteChar(&bufferTest, 'D');

    actual = isBufferEqualsToString(&bufferTest, "HELLO");
    // There is too much data in the buffer
    TEST_ASSERT_FALSE(actual);

    TEST_ASSERT_FALSE(isThereAnyError());
}

// writeChar

void test_bufferWriteChar(void) {
    initBufferForTest();

    bufferWriteChar(&bufferTest, 't');

    bool actual = isThereAnyError();
    TEST_ASSERT_FALSE(actual);
}

void test_bufferWriteChar_too_much_writes(void) {
    initBufferForTest();

    int i;
    for (i = 0; i < TEST_BUFFER_SIZE - 1; i++) {
        bufferWriteChar(&bufferTest, 'a' + i);
    }
    bool actual = isThereAnyError();
    TEST_ASSERT_FALSE(actual);

    bufferWriteChar(&bufferTest, '_');

    int lastError = getLastError();
    TEST_ASSERT_EQUAL(IO_BUFFER_FULL, lastError);
}

void test_bufferWriteChar_and_read_several_times(void) {
    initBufferForTest();

    int i;
    int j;

    const WRITE_READ_ITERATION_COUNT = 26;

    // Repeat write and read several times to see if there is no error
    for (j = 0; j < 10; j++) {

        for (i = 0; i < WRITE_READ_ITERATION_COUNT; i++) {
            bufferWriteChar(&bufferTest, 'a' + i);

            bool actual = isThereAnyError();
            TEST_ASSERT_FALSE(actual);
        }

        for (i = 0; i < WRITE_READ_ITERATION_COUNT; i++) {
            char value = bufferReadChar(&bufferTest);

            TEST_ASSERT_EQUAL('a' + i, value);

            bool actual = isThereAnyError();
            TEST_ASSERT_FALSE(actual);
        }
    }
}

void test_bufferWriteCharAtIndex(void) {
    initBufferForTest();
    bufferWriteChar(&bufferTest, 'H');
    bufferWriteChar(&bufferTest, 'E');
    bufferWriteChar(&bufferTest, 'L');
    bufferWriteChar(&bufferTest, 'L');
    bufferWriteChar(&bufferTest, 'O');
    bufferWriteCharAtIndex(&bufferTest, 1, 'A');

    bool actual = isBufferEqualsToString(&bufferTest, "HALLO");
    TEST_ASSERT_TRUE(actual);

}

// bufferGetCharAtIndex

void test_bufferGetCharAtIndex(void) {
    initBufferForTest();

    int i;

    const WRITE_READ_ITERATION_COUNT = 26;

    for (i = 0; i < WRITE_READ_ITERATION_COUNT; i++) {
        bufferWriteChar(&bufferTest, 'a' + i);

        bool actual = isThereAnyError();
        TEST_ASSERT_FALSE(actual);
    }

    for (i = 0; i < WRITE_READ_ITERATION_COUNT; i++) {
        char value = bufferGetCharAtIndex(&bufferTest, i);

        TEST_ASSERT_EQUAL('a' + i, value);
    }
}

// getBufferCapacity

void test_getBufferCapacity(void) {
    initBufferForTest();

    int bufferCapacity = getBufferCapacity(&bufferTest);

    TEST_ASSERT_EQUAL(TEST_BUFFER_SIZE - 1, bufferCapacity);
}

// clearBuffer

void test_clearBuffer(void) {
    initBufferForTest();

    int i;
    for (i = 0; i < TEST_BUFFER_SIZE / 2; i++) {
        bufferWriteChar(&bufferTest, 'a' + i);
    }
    int actual = getBufferElementsCount(&bufferTest);
    TEST_ASSERT_EQUAL(TEST_BUFFER_SIZE / 2, actual);

    clearBuffer(&bufferTest);

    actual = getBufferElementsCount(&bufferTest);
    TEST_ASSERT_EQUAL(0, actual);
}

// deepClearBuffer

void test_deepClearBuffer(void) {
    initBufferForTest();

    int i;
    for (i = 0; i < TEST_BUFFER_SIZE - 1; i++) {
        bufferWriteChar(&bufferTest, 'a' + i);
    }

    deepClearBuffer(&bufferTest);

    int actual = getBufferElementsCount(&bufferTest);
    TEST_ASSERT_EQUAL(0, actual);

    for (i = 0; i < TEST_BUFFER_SIZE; i++) {
        char* sPointer = (char*) bufferTest.s;
        // Shift to the right cell index
        sPointer += i;
        char value = *sPointer;
        TEST_ASSERT_EQUAL(0, value);
    }
}

// getOutputStream

void test_getOutputStream(void) {
    initBufferForTest();
    OutputStream* outputStream = getOutputStream(&bufferTest);

    TEST_ASSERT_FALSE(isThereAnyError());
    TEST_ASSERT_NOT_NULL(outputStream);
}

void test_getOutputStream_if_buffer_null(void) {
    initNullBufferForTest();
    OutputStream* outputStream = getOutputStream(&bufferTest);

    TEST_ASSERT_EQUAL(IO_BUFFER_NULL, getLastError());
    TEST_ASSERT_NOT_NULL(outputStream);
}

// getInputStream

void test_getInputStream(void) {
    initBufferForTest();
    InputStream* inputStream = getInputStream(&bufferTest);

    TEST_ASSERT_FALSE(isThereAnyError());
    TEST_ASSERT_NOT_NULL(inputStream);

}

void test_getInputStream_if_buffer_null(void) {
    initNullBufferForTest();
    InputStream* inputStream = getInputStream(&bufferTest);

    TEST_ASSERT_EQUAL(IO_BUFFER_NULL, getLastError());
    TEST_ASSERT_NOT_NULL(inputStream);
}