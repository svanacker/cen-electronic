#include <stdlib.h>
#include <stdbool.h>
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

void printAssertBooleanValue(bool value) {
    if (value) {
        printAssertMessage("true");
    }
    else {
        printAssertMessage("false");
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
    printAssertMessage("KO !!!\n");
}

void printTestOk(char* testName) {
    printTestName(testName);
    printAssertMessage("OK\n");
}

void runTest(TestSuite* testSuite, int testIndex) {
    appendCRLF(getTestOutputStream());
    appendString(getTestOutputStream(), testSuite->testSuiteName);
    appendCRLF(getTestOutputStream());

    TestFunction* testFunction = testSuite->testFunctions[testIndex];
    char* testName = testSuite->testNames[testIndex];
    bool testResult = testFunction();
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

bool assertNumericEquals(long expected, long actual, char* messageIfFailed) {
    if (expected != actual) {
        printExpectedDecValue(expected);
        printActualDecValue(expected);
        printAssertMessage(messageIfFailed);
        return false;
    }
    return true;
}

// Implementation

bool assertCharEquals(char expected, char actual, char* messageIfFailed) {
    return assertNumericEquals(expected, actual, messageIfFailed);
}

bool assertIntEquals(int expected, int actual, char* messageIfFailed) {
    return assertNumericEquals(expected, actual, messageIfFailed);
}

bool assertLongEquals(long expected, long actual, char* messageIfFailed) {
    return assertNumericEquals(expected, actual, messageIfFailed);
}

bool assertTrue(bool actual, char* messageIfFailed) {
    if (!actual) {
        printAssertExpected();
        printAssertBooleanValue(true);
        printAssertActual();
        printAssertBooleanValue(false);
        printAssertMessage(messageIfFailed);
        return false;
    }
    return true;
}

bool assertFalse(bool actual, char* messageIfFailed) {
    if (actual) {
        printAssertExpected();
        printAssertBooleanValue(false);
        printAssertActual();
        printAssertBooleanValue(true);
        printAssertMessage(messageIfFailed);
        return false;
    }
    return true;
}

// Pointer tests

bool assertPointerNotNull(int* actual, char* messageIfFailed) {
    if (actual == NULL) {
        printAssertExpected();
        printAssertMessage("NOT NULL");
        printAssertActual();
        printAssertMessage("NULL");
        printAssertMessage(messageIfFailed);
        return false;
    }
    return true;
}

// Object tests

/*
bool assertEquals(EqualsFunction* equalsFunction, int* actualObject, int* expectedObject, char* messageIfFailed) {
    bool equals = equalsFunction(actualObject, expectedObject);
    return assertTrue(equals, messageIfFailed);
}
*/

bool assertBufferEquals(Buffer* expectedBuffer, Buffer* actualBuffer, char* messageIfFailed) {
    // TODO : A Implémenter
    return false;
}
