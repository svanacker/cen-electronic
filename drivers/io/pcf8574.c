#include "../../common/commons32.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

#include "pcf8574.h"

#include "../../common/delay/delay30F.h"
#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../common/io/printWriter.h"

unsigned char internalGetAddress(unsigned char addr, unsigned char devAddr) {
    unsigned char result;
    result = addr | ((devAddr & 0x07) << 1);
    return result;
}

char isPCF8574Present(unsigned char addr, unsigned char devAddr) {
    char result;
    unsigned char realAddress = internalGetAddress(addr, devAddr);
    WaitI2C();
    portableStartI2C();
    WaitI2C();
	portableMasterWaitSendI2C();
    result = portableMasterWriteI2C(realAddress);
    WaitI2C();
    portableStopI2C();

    return result;
}

void writePCF8574(unsigned char addr, unsigned char devAddr, unsigned char outData, unsigned char dirs) {
    unsigned char realAddress = internalGetAddress(addr, devAddr);
    WaitI2C();
    portableStartI2C();
    WaitI2C();
	portableMasterWaitSendI2C();
    portableMasterWriteI2C(realAddress); // send write addres
    WaitI2C();
    portableMasterWriteI2C(outData | dirs); // write new outputs to buffer
    WaitI2C();
    portableMasterWriteI2C(outData | dirs); // force data to output pins
    WaitI2C();
    portableStopI2C();
}

unsigned char readPCF8574(unsigned char addr, unsigned char devAddr, unsigned char dirs) {
    unsigned char result;
    unsigned char realAddress = internalGetAddress(addr, devAddr);
    WaitI2C();
    portableStartI2C();
	portableMasterWaitSendI2C();
    // send read address (bit zero is set)
    portableMasterWriteI2C(realAddress | 1);
    WaitI2C();
    result = portableMasterReadI2C();
    //AckI2C();
    portableStopI2C();

    return (result & dirs);
}

void testPCF8574(OutputStream* outputStream) {
    char data;
    // PCF 0
    appendString(outputStream, "PCFADD0=");
    data = readPCF8574(0x40, 0, 0xFF);
    appendHex2(outputStream, data);
    delaymSec(150);
    // PCF 1
    appendString(outputStream, " PCFADD1 : ");
    data = readPCF8574(0x40, 1, 0xFF);
    appendHex2(outputStream, data);
    delaymSec(500);
}
