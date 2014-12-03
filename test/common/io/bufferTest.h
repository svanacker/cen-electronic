#ifndef BUFFER_TEST_H
#define BUFFER_TEST_H

void bufferTestSuite(void);

// initBuffer

void test_initBuffer_with_null_buffer_should_throw_buffer_null_error(void);

void test_initBuffer_should_be_right_initialized_and_empty_and_not_full(void);

void test_initBuffer_should_throw_error_when_empty_and_reading_char(void);

// writeChar

void test_bufferWriteChar(void);

void test_bufferWriteChar_too_much_writes(void);

void test_bufferWriteChar_and_read_several_times(void);

// isBufferEqualsToString

void test_isBufferEqualsToString(void);

// bufferGetCharAtIndex

void test_bufferGetCharAtIndex(void);

// bufferCapacity

void test_getBufferCapacity(void);

// clearBuffer

void test_clearBuffer(void);

// clearDeepBuffer

void test_deepClearBuffer(void);

// getOutputStream

void test_getOutputStream(void);

void test_getOutputStream_if_buffer_null(void);

// getInputStream

void test_getInputStream(void);

void test_getInputStream_if_buffer_null(void);

#endif
