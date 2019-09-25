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
    appendCRLF(getDebugOutputStreamLogger());
    appendString(getDebugOutputStreamLogger(), "absLongTest\n");
    appendString(getDebugOutputStreamLogger(), "NORMAL=");
    appendDec(getDebugOutputStreamLogger(), value);
    appendCRLF(getDebugOutputStreamLogger());

    appendString(getDebugOutputStreamLogger(), "RESULT=");
    appendDec(getDebugOutputStreamLogger(), absValue);
    appendCRLF(getDebugOutputStreamLogger());
    */

}

bool absLimitTest(void) {
    signed long value1 = 50000;
    signed long limitValue = 40000;

    signed long result = limit(value1, limitValue);
    
    appendCRLF(getDebugOutputStreamLogger());
    appendString(getDebugOutputStreamLogger(), "absLimitTest\n");
    appendString(getDebugOutputStreamLogger(), "NORMAL=");
    appendDec(getDebugOutputStreamLogger(), limitValue);
    appendCRLF(getDebugOutputStreamLogger());

    appendString(getDebugOutputStreamLogger(), "RESULT=");
    appendDec(getDebugOutputStreamLogger(), result);
    appendCRLF(getDebugOutputStreamLogger());

    return false;
}

bool absFloatTest(void) {
    signed long value = 40000.0;
    signed long absValue = fabsf(value);
    
    appendCRLF(getDebugOutputStreamLogger());
    appendString(getDebugOutputStreamLogger(), "absFloatTest\n");
    appendString(getDebugOutputStreamLogger(), "NORMAL=");
    appendDecf(getDebugOutputStreamLogger(), value);
    appendCRLF(getDebugOutputStreamLogger());

    appendString(getDebugOutputStreamLogger(), "RESULT=");
    appendDecf(getDebugOutputStreamLogger(), absValue);
    appendCRLF(getDebugOutputStreamLogger());

    return false;
}

bool convertFloatTest1(void) {
    signed long value = 40000;
    float result = (float) value;
    
    appendCRLF(getDebugOutputStreamLogger());
    appendString(getDebugOutputStreamLogger(), "convertFloatTest1\n");
    appendString(getDebugOutputStreamLogger(), "NORMAL=40000.0000");
    appendCRLF(getDebugOutputStreamLogger());

    appendString(getDebugOutputStreamLogger(), "RESULT=");
    appendDecf(getDebugOutputStreamLogger(), result);
    appendCRLF(getDebugOutputStreamLogger());

    return false;
}

bool convertFloatTest2(void) {
    signed long value = -40000;
    float result = (float) value;
    
    appendCRLF(getDebugOutputStreamLogger());
    appendString(getDebugOutputStreamLogger(), "convertFloatTest2\n");
    appendString(getDebugOutputStreamLogger(), "NORMAL=-40000.0000");
    appendCRLF(getDebugOutputStreamLogger());

    appendString(getDebugOutputStreamLogger(), "RESULT=");
    appendDecf(getDebugOutputStreamLogger(), result);
    appendCRLF(getDebugOutputStreamLogger());

    return false;
}

bool convertFloatTest3(void) {
    signed long value = -123456789;
    float result = (float) value;
    
    appendCRLF(getDebugOutputStreamLogger());
    appendString(getDebugOutputStreamLogger(), "convertFloatTest2\n");
    appendString(getDebugOutputStreamLogger(), "NORMAL=-123456789.0000");
    appendCRLF(getDebugOutputStreamLogger());

    appendString(getDebugOutputStreamLogger(), "RESULT=");
    appendDecf(getDebugOutputStreamLogger(), result);
    appendCRLF(getDebugOutputStreamLogger());

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
