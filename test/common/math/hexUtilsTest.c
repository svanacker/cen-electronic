#include "../../../common/math/hexUtils.h"
#include "../../../test/unity/unity.h"

void test_hex2CharToInt_should_equal_to_0_if_0(void) {
	int actual = hex2CharToInt(0, 0);

	TEST_ASSERT_EQUAL(0, actual);
}
