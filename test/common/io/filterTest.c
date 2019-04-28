#include "filterTest.h"

#include <stdbool.h>

#include "../../../common/commons.h"
#include "../../../common/io/filter.h"

#include "../../../test/unity/unity.h"

void filterTestSuite(void) {
    RUN_TEST(test_filterBinaryToValueChar);
    RUN_TEST(test_filterRemoveCRLF);
}

// test_filterBinaryToValueChar

void test_filterBinaryToValueChar(void) {
    char output;
    char* outputPointer = &output;
    bool actual;

    // '\0' -> filtered ! & outputPointer
    actual = filterBinaryToValueChar('\0', outputPointer);
    TEST_ASSERT_FALSE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, '\0');

    // '\3' -> filtered ! & outputPointer
    actual = filterBinaryToValueChar('\3', outputPointer);
    TEST_ASSERT_FALSE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, '\3');

    // '\31' -> filtered ! & outputPointer
    actual = filterBinaryToValueChar('\31', outputPointer);
    TEST_ASSERT_FALSE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, '\31');
    
    // '1' -> 1
    actual = filterBinaryToValueChar('1', outputPointer);

    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, 1);

    // 'E' -> 14
    actual = filterBinaryToValueChar('E', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, 14);

    // 'G' -> value of 'G'
    actual = filterBinaryToValueChar('G', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, 'G');

    // 'P' -> value of 'P'
    actual = filterBinaryToValueChar('P', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, 'P');

    // 'Z' -> value of 'Z'
    actual = filterBinaryToValueChar('Z', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, 'Z');

    // 'a' -> value of 'a'
    actual = filterBinaryToValueChar('a', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, 'a');

    // 'h' -> value of 'h'
    actual = filterBinaryToValueChar('h', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, 'h');

    // 'z' -> value of 'z'
    actual = filterBinaryToValueChar('z', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, 'z');

    // ':' -> value of ':'
    actual = filterBinaryToValueChar(':', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, ':');

    // '@' -> value of '@'
    actual = filterBinaryToValueChar('@', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, '@');

    // '|' -> value of '|'
    actual = filterBinaryToValueChar('|', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, '|');

    // 'value > 128 / < 0' -> value of '@'
    actual = filterBinaryToValueChar(-2, outputPointer);
    TEST_ASSERT_FALSE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, -2);

    // < 0
    actual = filterBinaryToValueChar(-65, outputPointer);
    TEST_ASSERT_FALSE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, -65);
}

void test_filterRemoveCRLF(void) {
    char output;
    char* outputPointer = &output;
    bool actual;

    // '\1' -> '\1'
    actual = filterRemoveCRLF('\1', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, '\1');

    // 'a' -> 'a'
    actual = filterRemoveCRLF('a', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, 'a');

    // LF -> LF but returns false
    actual = filterRemoveCRLF(LF, outputPointer);
    TEST_ASSERT_FALSE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, LF);

    // CR -> CR but returns false
    actual = filterRemoveCRLF(CR, outputPointer);
    TEST_ASSERT_FALSE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, CR);

}

void test_filterRemoveCRLF_255(void) {
    char output;
    char* outputPointer = &output;
    bool actual;

    // '\1' -> '\1'
    actual = filterRemoveCRLF('\1', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, '\1');

    // 'a' -> 'a'
    actual = filterRemoveCRLF('a', outputPointer);
    TEST_ASSERT_TRUE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, 'a');

    // LF -> LF but returns false
    actual = filterRemoveCRLF(LF, outputPointer);
    TEST_ASSERT_FALSE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, LF);

    // CR -> CR but returns false
    actual = filterRemoveCRLF(CR, outputPointer);
    TEST_ASSERT_FALSE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, CR);

    // "ÿ" = '\255'
    actual = filterRemoveCRLF_255('ÿ', outputPointer);
    TEST_ASSERT_FALSE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, 'ÿ');

    // "ÿ" = '\255'
    actual = filterRemoveCRLF_255('\255', outputPointer);
    TEST_ASSERT_FALSE(actual);
    TEST_ASSERT_EQUAL(*outputPointer, '\255');
}