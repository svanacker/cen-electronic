#ifndef PIC_UNIT_H
#define PIC_UNIT_H

#include <stdbool.h>
#include "../../common/commons.h"
#include "../../common/io/buffer.h"

/**
* Defines a function which do a test
* @return true if the test is ok, false else
*/
typedef bool TestFunction();

/** The max limit of test suite. */
#define MAX_TEST_COUNT 20

/**
* The struct defining a list of test.
*/
typedef struct TestSuite {
    /** The name of the test Suite. */
    char* testSuiteName;
    /** An array of test function pointer. */
    TestFunction* testFunctions[MAX_TEST_COUNT];
    /** An array of test name. */
    char* testNames[MAX_TEST_COUNT];
    /** The number of test ok. */
    unsigned char okCount;
    /** The number of test failed. */
    unsigned char failedCount;
    /** the size of the list. */
    unsigned char size;
} TestSuite;

OutputStream* getTestOutputStream();

/**
* Add a test to a testSuite.
*/
void addTest(TestSuite* testSuite, TestFunction* testFunction, char* testName);

/**
* Run a suite of tests and print Statistics.
* @param testSuite the pointer on the test suite.
*/
void runTestSuite(TestSuite* testSuite);

// Arithmetics/Logical tests

/**
* Test if 2 chars are equals or not, and produces a message if it's not the case.
*/
bool assertCharEquals(char expected, char actual, char* messageIfFailed);

/**
* Test if 2 int are equals or not, and produces a message if it's not the case.
*/
bool assertIntEquals(int expected, int actual, char* messageIfFailed);

/**
* Test if 2 longs are equals or not, and produces a message if it's not the case.
*/
bool assertLongEquals(long expected, long actual, char* messageIfFailed);

/**
* Test if a value is true, and produces a message if it's not the case.
*/
bool assertTrue(bool actual, char* messageIfFailed);

/**
* Test if a value is false, and produces a message if it's not the case.
*/
bool assertFalse(bool actual, char* messageIfFailed);

// Pointer tests

/**
* Assert a pointer (generally on a structure) is not empty.
*/
bool assertPointerNotNull(int* actual, char* messageIfFailed);

// Object tests

/**
* Assert that 2 objects are equals using a equalsFunction.
*/
// bool assertEquals(EqualsFunction* equalsFunction, int* actual, int* expected, char* messageIfFailed);

/**
* Classic implementation
*/
bool assertBufferEquals(Buffer* expectedBuffer, Buffer* actualBuffer, char* messageIfFailed);

// Print Functions

/**
* Print if a test is ok.
*/
void printTestOk(char* testName);

/**
* Print if a test fail.
*/
void printTestFailed(char* testName);


#endif
