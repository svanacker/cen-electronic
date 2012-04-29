#include <stdlib.h>
#include "picunit.h"

#include "../../common/commons.h"
#include "../../common/io/buffer.h"
#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"


// Primitives / Internal

OutputStream* getTestOutputStream() {
	return getOutputStreamLogger(ALWAYS);
}

void printAssertMessage(char* message) {
	appendString(getTestOutputStream(), message);
}

void printAssertDecValue(long value) {
	appendDec(getTestOutputStream(), value);
}

void printAssertDecfValue(float value) {
	appendDecf(getTestOutputStream(), value);
}

void printAssertBooleanValue(BOOL value) {
	if (value) {
		printAssertMessage("TRUE");
	}
	else {
		printAssertMessage("FALSE");
	}
}

// TestSuite

void addTest(TestSuite* testSuite, TestFunction* testFunction, char* testName) {
	unsigned char size = testSuite->size;
	if (size < MAX_TEST_COUNT) {
		testSuite->testFunctions[size] = testFunction;		
		testSuite->testNames[size] = testName;		
		testSuite->size++;
	}
	else {
		appendString(getTestOutputStream(), "Too much tests in testSuite");
	}
}

void printTestSuiteResult(TestSuite* testSuite) {
	appendString(getTestOutputStream(), "TestSuite:");
}


void printTestName(char* testName) {
	printAssertMessage(testName);
	printAssertMessage(":");
}

void printTestFailed(char* testName) {
	printTestName(testName);
	printAssertMessage("OK\n");
}

void printTestOk(char* testName) {
	printTestName(testName);
	printAssertMessage("KO !!!\n");
}

void runTest(TestSuite* testSuite, int testIndex) {
	appendCRLF(getTestOutputStream());
	appendString(getTestOutputStream(), testSuite->testSuiteName);
	appendCRLF(getTestOutputStream());

	TestFunction* testFunction = testSuite->testFunctions[testIndex];
	char* testName = testSuite->testNames[testIndex];
	BOOL testResult = testFunction();
	if (testResult) {
		printTestOk(testName);
		testSuite->okCount++;
	}
	else {
		printTestFailed(testName);
		testSuite->okCount++;
	}
}

void runTestSuite(TestSuite* testSuite) {
	testSuite->okCount = 0;
	testSuite->failedCount = 0;
	
	int i;
	for (i = 0; i < testSuite->size; i++) {
		runTest(testSuite, i);
	}
	printTestSuiteResult(testSuite);
}

void printAssertActual() {
	printAssertMessage("ACTUAL=");
}

void printAssertExpected() {
	printAssertMessage("EXPECTED=");
}

void printExpectedDecValue(long expected) {
	printAssertExpected();
	printAssertDecValue(expected);
	printAssertMessage("\n");
}

void printActualDecValue(long actual) {
	printAssertActual();
	printAssertDecValue(actual);
	printAssertMessage("\n");
}

void printExpectedDecfValue(long expected) {
	printAssertExpected();
	printAssertDecfValue(expected);
	printAssertMessage("\n");
}

void printActualDecfValue(long actual) {
	printAssertActual();
	printAssertDecfValue(actual);
	printAssertMessage("\n");
}

BOOL assertNumericEquals(long expected, long actual, char* messageIfFailed) {
	if (expected != actual) {
		printExpectedDecValue(expected);
		printActualDecValue(expected);
		printAssertMessage(messageIfFailed);
		return FALSE;
	}
	return TRUE;
}

// Implementation

BOOL assertCharEquals(char expected, char actual, char* messageIfFailed) {
	return assertNumericEquals(expected, actual, messageIfFailed);
}

BOOL assertIntEquals(int expected, int actual, char* messageIfFailed) {
	return assertNumericEquals(expected, actual, messageIfFailed);
}

BOOL assertLongEquals(long expected, long actual, char* messageIfFailed) {
	return assertNumericEquals(expected, actual, messageIfFailed);
}

BOOL assertTrue(BOOL actual, char* messageIfFailed) {
	if (!actual) {
		printAssertExpected();
		printAssertBooleanValue(TRUE);
		printAssertActual();
		printAssertBooleanValue(FALSE);
		printAssertMessage(messageIfFailed);
		return FALSE;
	}
	return TRUE;
}

BOOL assertFalse(BOOL actual, char* messageIfFailed) {
	if (actual) {
		printAssertExpected();
		printAssertBooleanValue(FALSE);
		printAssertActual();
		printAssertBooleanValue(TRUE);
		printAssertMessage(messageIfFailed);
		return FALSE;
	}
	return TRUE;
}

// Pointer tests

BOOL assertPointerNotNull(int* actual, char* messageIfFailed) {
	if (actual == NULL) {
		printAssertExpected();
		printAssertMessage("NOT NULL");
		printAssertActual();
		printAssertMessage("NULL");
		printAssertMessage(messageIfFailed);
		return FALSE;
	}
	return TRUE;
}

// Object tests

BOOL assertEquals(EqualsFunction* equalsFunction, int* actualObject, int* expectedObject, char* messageIfFailed) {
	BOOL equals = equalsFunction(actualObject, expectedObject);
	return assertTrue(equals, messageIfFailed);
}

BOOL assertBufferEquals(Buffer* expectedBuffer, Buffer* actualBuffer, char* messageIfFailed) {
	// TODO : A Implémenter
	return FALSE;
}
