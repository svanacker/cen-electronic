#include "compositeOutputStreamTest.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/compositeOutputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"

#include "../../../test/unity/unity.h"

static CompositeOutputStream compositeOutputStream;
#define TEST_COMPOSITE_OUTPUT_STREAM_BUFFER_SIZE    10

static OutputStream* outputStream1;
static Buffer buffer1;
static char bufferArrayTest1[TEST_COMPOSITE_OUTPUT_STREAM_BUFFER_SIZE];

static Buffer buffer2;
static char bufferArrayTest2[TEST_COMPOSITE_OUTPUT_STREAM_BUFFER_SIZE];
static OutputStream* outputStream2;

#define COMPOSITE_OUTPUT_STREAM_TEST_LIST_ARRAY_LENGTH 2
static OutputStream* outputStreamListArray[COMPOSITE_OUTPUT_STREAM_TEST_LIST_ARRAY_LENGTH];

void compositeOutputStreamTestSuite(void) {
    RUN_TEST(test_init_compositeOutputStream);
}

void test_init_compositeOutputStream(void) {
    initBuffer(&buffer1, (char(*)[]) &bufferArrayTest1, TEST_COMPOSITE_OUTPUT_STREAM_BUFFER_SIZE, "compositeOutputStreamTest1", "compositeOutputStreamType");
    outputStream1 = getOutputStream(&buffer1);

    initBuffer(&buffer2, (char(*)[]) &bufferArrayTest2, TEST_COMPOSITE_OUTPUT_STREAM_BUFFER_SIZE, "compositeOutputStreamTest2", "compositeOutputStreamType");
    outputStream2 = getOutputStream(&buffer2);

    initCompositeOutputStream(&compositeOutputStream, (OutputStream*(*)[]) outputStreamListArray, COMPOSITE_OUTPUT_STREAM_TEST_LIST_ARRAY_LENGTH);
    addOutputStream(&compositeOutputStream, outputStream1);
    addOutputStream(&compositeOutputStream, outputStream2);

    OutputStream* outputStream = &(compositeOutputStream.outputStream);

    
    TEST_ASSERT_TRUE(isBufferEmpty(&buffer1));
    TEST_ASSERT_TRUE(isBufferEmpty(&buffer2));

    append(outputStream, 't');

    TEST_ASSERT_FALSE(isBufferEmpty(&buffer1));
    TEST_ASSERT_FALSE(isBufferEmpty(&buffer2));
}