#include <math.h>

#include "../common/io/inputStream.h"
#include "../common/io/outputStream.h"
#include "../common/io/ioUtils.h"
#include "../common/io/printWriter.h"
#include "../common/io/stream.h"

#include "../common/picunit/picunit.h"

#include "../common/log/logger.h"
#include "../common/log/logLevel.h"

#include "../common/math/cenMath.h"

static TestSuite mathTestSuite;

/**
* Test if there is no overflow using 16 bits with absLong function.
*/
bool absLongTest(void) {
	signed long value = 40000;
	signed long absValue = absLong(value);

	return assertLongEquals(value, absValue, "");

	/*	
	appendCRLF(getOutputStreamLogger(DEBUG));
	appendString(getOutputStreamLogger(DEBUG), "absLongTest\n");
	appendString(getOutputStreamLogger(DEBUG), "NORMAL=");
	appendDec(getOutputStreamLogger(DEBUG), value);
	appendCRLF(getOutputStreamLogger(DEBUG));

	appendString(getOutputStreamLogger(DEBUG), "RESULT=");
	appendDec(getOutputStreamLogger(DEBUG), absValue);
	appendCRLF(getOutputStreamLogger(DEBUG));
	*/

}

bool absLimitTest(void) {
	signed long value1 = 50000;
	signed long limitValue = 40000;

	signed long result = limit(value1, limitValue);
	
	appendCRLF(getOutputStreamLogger(DEBUG));
	appendString(getOutputStreamLogger(DEBUG), "absLimitTest\n");
	appendString(getOutputStreamLogger(DEBUG), "NORMAL=");
	appendDec(getOutputStreamLogger(DEBUG), limitValue);
	appendCRLF(getOutputStreamLogger(DEBUG));

	appendString(getOutputStreamLogger(DEBUG), "RESULT=");
	appendDec(getOutputStreamLogger(DEBUG), result);
	appendCRLF(getOutputStreamLogger(DEBUG));

	return false;
}

bool absFloatTest(void) {
	signed long value = 40000.0;
	signed long absValue = fabsf(value);
	
	appendCRLF(getOutputStreamLogger(DEBUG));
	appendString(getOutputStreamLogger(DEBUG), "absFloatTest\n");
	appendString(getOutputStreamLogger(DEBUG), "NORMAL=");
	appendDecf(getOutputStreamLogger(DEBUG), value);
	appendCRLF(getOutputStreamLogger(DEBUG));

	appendString(getOutputStreamLogger(DEBUG), "RESULT=");
	appendDecf(getOutputStreamLogger(DEBUG), absValue);
	appendCRLF(getOutputStreamLogger(DEBUG));

	return false;
}

bool convertFloatTest1(void) {
	signed long value = 40000;
	float result = (float) value;
	
	appendCRLF(getOutputStreamLogger(DEBUG));
	appendString(getOutputStreamLogger(DEBUG), "convertFloatTest1\n");
	appendString(getOutputStreamLogger(DEBUG), "NORMAL=40000.0000");
	appendCRLF(getOutputStreamLogger(DEBUG));

	appendString(getOutputStreamLogger(DEBUG), "RESULT=");
	appendDecf(getOutputStreamLogger(DEBUG), result);
	appendCRLF(getOutputStreamLogger(DEBUG));

	return false;
}

bool convertFloatTest2(void) {
	signed long value = -40000;
	float result = (float) value;
	
	appendCRLF(getOutputStreamLogger(DEBUG));
	appendString(getOutputStreamLogger(DEBUG), "convertFloatTest2\n");
	appendString(getOutputStreamLogger(DEBUG), "NORMAL=-40000.0000");
	appendCRLF(getOutputStreamLogger(DEBUG));

	appendString(getOutputStreamLogger(DEBUG), "RESULT=");
	appendDecf(getOutputStreamLogger(DEBUG), result);
	appendCRLF(getOutputStreamLogger(DEBUG));

	return false;
}

bool convertFloatTest3(void) {
	signed long value = -123456789;
	float result = (float) value;
	
	appendCRLF(getOutputStreamLogger(DEBUG));
	appendString(getOutputStreamLogger(DEBUG), "convertFloatTest2\n");
	appendString(getOutputStreamLogger(DEBUG), "NORMAL=-123456789.0000");
	appendCRLF(getOutputStreamLogger(DEBUG));

	appendString(getOutputStreamLogger(DEBUG), "RESULT=");
	appendDecf(getOutputStreamLogger(DEBUG), result);
	appendCRLF(getOutputStreamLogger(DEBUG));

	return false;
}

TestSuite* getMathTestSuite() {
	mathTestSuite.size = 0;
	mathTestSuite.testSuiteName = "MATH TEST SUITE";
	addTest(&mathTestSuite, &absLongTest, "absLongTest");
	addTest(&mathTestSuite, absLimitTest, "absLimitTest");
	addTest(&mathTestSuite, absFloatTest, "absFloatTest");
	addTest(&mathTestSuite, convertFloatTest1, "convertFloatTest1");
	addTest(&mathTestSuite, convertFloatTest2, "convertFloatTest2");
	addTest(&mathTestSuite, convertFloatTest3, "convertFloatTest3");
	return &mathTestSuite;
}
