#include "pcf8574.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

unsigned char internalGetAddress(I2cBus* i2cBus, unsigned char addr, unsigned char devAddr) {
    unsigned char result;
    result = addr | ((devAddr & 0x07) << 1);
    return result;
}

char isPCF8574Present(I2cBus* i2cBus, unsigned char addr, unsigned char devAddr) {
    char result;
    unsigned char realAddress = internalGetAddress(i2cBus, addr, devAddr);
    WaitI2C(i2cBus);
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBus);
    result = portableMasterWriteI2C(i2cBus, realAddress);
    WaitI2C(i2cBus);
    portableStopI2C(i2cBus);

    return result;
}

void writePCF8574(I2cBus* i2cBus, unsigned char addr, unsigned char devAddr, unsigned char outData, unsigned char dirs) {
    unsigned char realAddress = internalGetAddress(i2cBus, addr, devAddr);
    WaitI2C(i2cBus);
    portableStartI2C(i2cBus);
    WaitI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, realAddress); // send write address
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, outData | dirs); // write new outputs to buffer
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBus, outData | dirs); // force data to output pins
    WaitI2C(i2cBus);
    portableStopI2C(i2cBus);
}

unsigned char readPCF8574(I2cBus* i2cBus, unsigned char addr, unsigned char devAddr, unsigned char dirs) {
    unsigned char result;
    unsigned char realAddress = internalGetAddress(i2cBus, addr, devAddr);
    WaitI2C(i2cBus);
    portableStartI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBus);
    // send read address (bit zero is set)
    portableMasterWriteI2C(i2cBus, realAddress | 1);
    WaitI2C(i2cBus);
    result = portableMasterReadI2C(i2cBus);
    //AckI2C();
    portableStopI2C(i2cBus);

    return (result & dirs);
}

void testPCF8574(I2cBus* i2cBus, OutputStream* outputStream) {
    char data;
    // PCF 0
    appendString(outputStream, "PCFADD0=");
    data = readPCF8574(i2cBus, 0x40, 0, 0xFF);
    appendHex2(outputStream, data);
    delaymSec(150);
    // PCF 1
    appendString(outputStream, " PCFADD1 : ");
    data = readPCF8574(i2cBus, 0x40, 1, 0xFF);
    appendHex2(outputStream, data);
    delaymSec(500);
}
