#include <stdio.h>
#include <stdlib.h>

#include "common/error/error.h"
#include "test/unity/unity.h"

#include "test/common/io/bufferTest.h"
#include "test/common/io/filterTest.h"
#include "test/common/io/ioUtilsTest.h"
#include "test/common/io/printWriterTest.h"
#include "test/common/io/readerTest.h"

#include "test/common/math/hexUtilsTest.h"

void setUp(void)
{
	clearLastError();
}

void tearDown(void)
{
}



int main(int argc, char *argv[])
{
	UnityBegin("cen-electronic-console");

	// RUN_TEST calls runTest
	hexUtilsTestSuite();
	bufferTestSuite();
	filterTestSuite();
	printWriterTestSuite();
	readerTestSuite();
	ioUtilsTestSuite();

	UnityEnd();

	getchar();
	return EXIT_SUCCESS;
}


