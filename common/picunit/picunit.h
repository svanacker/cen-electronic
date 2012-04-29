#ifndef PIC_UNIT_H
#define PIC_UNIT_H

#include "../../common/commons.h"
#include "../../common/io/buffer.h"

/**
* Defines a function which do a test
* @return TRUE if the test is ok, FALSE else
*/
typedef BOOL TestFunction();

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
BOOL assertCharEquals(char expected, char actual, char* messageIfFailed);

/**
* Test if 2 int are equals or not, and produces a message if it's not the case.
*/
BOOL assertIntEquals(int expected, int actual, char* messageIfFailed);

/**
* Test if 2 longs are equals or not, and produces a message if it's not the case.
*/
BOOL assertLongEquals(long expected, long actual, char* messageIfFailed);

/**
* Test if a value is TRUE, and produces a message if it's not the case.
*/
BOOL assertTrue(BOOL actual, char* messageIfFailed);

/**
* Test if a value is FALSE, and produces a message if it's not the case.
*/
BOOL assertFalse(BOOL actual, char* messageIfFailed);

// Pointer tests

/**
* Assert a pointer (generally on a structure) is not empty.
*/
BOOL assertPointerNotNull(int* actual, char* messageIfFailed);

// Object tests

/**
* Assert that 2 objects are equals using a equalsFunction.
*/
BOOL assertEquals(EqualsFunction* equalsFunction, int* actual, int* expected, char* messageIfFailed);

/**
* Classic implementation
*/
BOOL assertBufferEquals(Buffer* expectedBuffer, Buffer* actualBuffer, char* messageIfFailed);

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
