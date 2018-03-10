#include "readerTest.h"

#include "../../../common/error/error.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/string/cenString.h"

#include "../../../test/unity/unity.h"

#define TEST_BUFFER_SIZE 20

static Buffer bufferTest;
static char bufferArrayTest[TEST_BUFFER_SIZE];
static OutputStream* outputStream;
static InputStream* inputStream;

void readerTestSuite(void) {
    RUN_TEST(test_readBool);
    RUN_TEST(test_readFilteredChar);
    RUN_TEST(test_readBinaryChar);
    RUN_TEST(test_readBinaryWord);
    RUN_TEST(test_readHex);
    RUN_TEST(test_readHex2);
    RUN_TEST(test_readSignedHex2);
    RUN_TEST(test_readHex4);
    RUN_TEST(test_readSignedHex4);
    RUN_TEST(test_readHex6);
    RUN_TEST(test_isAck);
    RUN_TEST(test_isChar);
    RUN_TEST(test_checkIsAck);
    RUN_TEST(test_checkIsChar);
    RUN_TEST(test_readHexFixedCharArray);
}

void initBufferForReaderTest(void) {
    initBuffer(&bufferTest, (char(*)[]) &bufferArrayTest, TEST_BUFFER_SIZE, "readerTest", "readerTestType");
    outputStream = getOutputStream(&bufferTest);
    inputStream = getInputStream(&bufferTest);
}

void test_readBool(void) {
    initBufferForReaderTest();

    appendString(outputStream, "015");

    bool value = readBool(inputStream);
    TEST_ASSERT_FALSE(value);
    TEST_ASSERT_EQUAL(0, getLastError());
    
    value = readBool(inputStream);
    TEST_ASSERT_TRUE(value);
    TEST_ASSERT_EQUAL(0, getLastError());

    value = readBool(inputStream);
    TEST_ASSERT_TRUE(value);
    TEST_ASSERT_EQUAL(IO_READER_NOT_BOOL_VALUE, getLastError());
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

    // FF, value > 127, but we are in unsigned mode
    value = readHex2(inputStream);
    TEST_ASSERT_EQUAL(255, value);
    TEST_ASSERT_EQUAL(0, getLastError());

    // 10
    value = readHex2(inputStream);
    TEST_ASSERT_EQUAL(16, value);
    TEST_ASSERT_EQUAL(0, getLastError());
}

void test_readSignedHex2(void) {
    initBufferForReaderTest();

    appendString(outputStream, "B5FF10");

    // B5
    signed int value = readSignedHex2(inputStream);
    TEST_ASSERT_EQUAL(-75, value);
    TEST_ASSERT_EQUAL(0, getLastError());

    // FF, value > 127, but we are in signed mode
    value = readSignedHex2(inputStream);
    TEST_ASSERT_EQUAL(-1, value);
    TEST_ASSERT_EQUAL(0, getLastError());

    // 10 : must be not signed value
    value = readSignedHex2(inputStream);
    TEST_ASSERT_EQUAL(16, value);
    TEST_ASSERT_EQUAL(0, getLastError());
}

void test_readHex4(void) {
    initBufferForReaderTest();

    appendString(outputStream, "B5FF103F");

    // B5FF, value > 35535, but we are in unsigned mode
    long value = readHex4(inputStream);
    TEST_ASSERT_EQUAL(46591, value);
    TEST_ASSERT_EQUAL(0, getLastError());

    // 103F
    value = readHex4(inputStream);
    TEST_ASSERT_EQUAL(4159, value);
    TEST_ASSERT_EQUAL(0, getLastError());
}


void test_readSignedHex4(void) {
    initBufferForReaderTest();

    appendString(outputStream, "B5FF103F");

    // B5FF, value > 35535, and we are in unsigned mode !
    signed long value = readSignedHex4(inputStream);
    TEST_ASSERT_EQUAL(-18945, value);
    TEST_ASSERT_EQUAL(0, getLastError());

    // 103F
    value = readSignedHex4(inputStream);
    TEST_ASSERT_EQUAL(4159, value);
    TEST_ASSERT_EQUAL(0, getLastError());
}

void test_readHex6(void) {
    initBufferForReaderTest();

    appendString(outputStream, "B5FF10");

    // Value is > 0 always
    long value = readHex6(inputStream);
    TEST_ASSERT_EQUAL(value, 11927312);
    TEST_ASSERT_EQUAL(0, getLastError());
}

void test_readHexFixedCharArray(void) {
    initBufferForReaderTest();
    appendHex2(outputStream, 'H');
    appendHex2(outputStream, 'E');
    appendHex2(outputStream, 'L');
    appendHex2(outputStream, 'L');

    FixedCharArray s;
    readHexFixedCharArray(inputStream, &s);

    TEST_ASSERT_EQUAL('H', s[0]);
    TEST_ASSERT_EQUAL('E', s[1]);
    TEST_ASSERT_EQUAL('L', s[2]);
    TEST_ASSERT_EQUAL('L', s[3]);
}

void test_isAck(void) {
    initBufferForReaderTest();

    appendString(outputStream, "aA\1");

    bool value = isAck(inputStream);
    TEST_ASSERT_TRUE(value);

    value = isAck(inputStream);
    TEST_ASSERT_FALSE(value);

    value = isAck(inputStream);
    TEST_ASSERT_FALSE(value);

    TEST_ASSERT_EQUAL(0, getLastError());
}

void test_isChar() {
    initBufferForReaderTest();

    appendString(outputStream, "bF\1");

    bool value = isChar(inputStream, 'b');
    TEST_ASSERT_TRUE(value);

    value = isChar(inputStream, 'G');
    TEST_ASSERT_FALSE(value);

    value = isChar(inputStream, '\1');
    TEST_ASSERT_TRUE(value);

    TEST_ASSERT_EQUAL(0, getLastError());
}

void test_checkIsAck() {
    initBufferForReaderTest();

    appendString(outputStream, "aA\1");

    bool value = checkIsAck(inputStream);
    TEST_ASSERT_TRUE(value);
    TEST_ASSERT_EQUAL(0, getLastError());

    value = checkIsAck(inputStream);
    TEST_ASSERT_FALSE(value);
    TEST_ASSERT_EQUAL(IO_READER_CHECK_CHAR_PROBLEM, getLastError());
    
    clearLastError();
    value = checkIsAck(inputStream);
    TEST_ASSERT_FALSE(value);

    TEST_ASSERT_EQUAL(IO_READER_CHECK_CHAR_PROBLEM, getLastError());
}

void test_checkIsChar() {
    initBufferForReaderTest();

    appendString(outputStream, "bF\1");

    bool value = checkIsChar(inputStream, 'b');
    TEST_ASSERT_TRUE(value);
    TEST_ASSERT_EQUAL(0, getLastError());

    clearLastError();
    value = checkIsChar(inputStream, 'G');
    TEST_ASSERT_FALSE(value);
    TEST_ASSERT_EQUAL(IO_READER_CHECK_CHAR_PROBLEM, getLastError());

    clearLastError();

    value = checkIsChar(inputStream, '\1');
    TEST_ASSERT_TRUE(value);
    TEST_ASSERT_EQUAL(0, getLastError());
}