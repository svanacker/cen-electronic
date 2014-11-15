#include <stdio.h>
#include <stdlib.h>
#include "common/math/hexUtils.h"

#include "test/unity/unity.h"
#include "test/common/math/hexUtilsTest.h"

void setUp(void)
{

}

void tearDown(void)
{
}

int main(int argc, char *argv[])
{
	int expected = 1;
	int actual = hex2CharToInt(0, 1);

	if (expected != actual) {
		printf("ERROR ! %d", actual);
	}
	else {
		printf("OK !");
	}

	UnityBegin("cen-electronic-console");

	// RUN_TEST calls runTest
	RUN_TEST(test_hex2CharToInt_should_equal_to_0_if_0);

	UnityEnd();

	getchar();
	return EXIT_SUCCESS;
}


