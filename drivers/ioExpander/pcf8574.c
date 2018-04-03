#include "pcf8574.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/delay/cenDelay.h"

#include "../../common/i2c/i2cCommon.h"
#include "../../common/i2c/master/i2cMaster.h"

#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "ioExpander.h"

#define PCF8574_IO_COUNT     ((unsigned int) 8)

// BASE FUNCTION

unsigned char internalGetAddress(I2cBusConnection* i2cBusConnection, unsigned char addr, unsigned char devAddr) {
    unsigned char result;
    result = addr | ((devAddr & 0x07) << 1);
    return result;
}

char isPCF8574Present(I2cBusConnection* i2cBusConnection, unsigned char addr, unsigned char devAddr) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    char result;
    unsigned char realAddress = internalGetAddress(i2cBusConnection, addr, devAddr);
    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBusConnection);
    result = portableMasterWriteI2C(i2cBusConnection, realAddress);
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);

    return result;
}

void writePCF8574(I2cBusConnection* i2cBusConnection, unsigned char addr, unsigned char devAddr, unsigned char outData, unsigned char dirs) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    unsigned char realAddress = internalGetAddress(i2cBusConnection, addr, devAddr);
    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);
    WaitI2C(i2cBus);
    portableMasterWaitSendI2C(i2cBusConnection);
    portableMasterWriteI2C(i2cBusConnection, realAddress); // send write address
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, outData | dirs); // write new outputs to buffer
    WaitI2C(i2cBus);
    portableMasterWriteI2C(i2cBusConnection, outData | dirs); // force data to output pins
    WaitI2C(i2cBus);
    portableMasterStopI2C(i2cBusConnection);
}

unsigned char readPCF8574(I2cBusConnection* i2cBusConnection, unsigned char addr, unsigned char devAddr, unsigned char dirs) {
    I2cBus* i2cBus = i2cBusConnection->i2cBus;

    unsigned char result;
    unsigned char realAddress = internalGetAddress(i2cBusConnection, addr, devAddr);
    WaitI2C(i2cBus);
    portableMasterStartI2C(i2cBusConnection);
    portableMasterWaitSendI2C(i2cBusConnection);
    // send read address (bit zero is set)
    portableMasterWriteI2C(i2cBusConnection, realAddress | 1);
    WaitI2C(i2cBus);
    result = portableMasterReadI2C(i2cBusConnection);
    //AckI2C();
    portableMasterStopI2C(i2cBusConnection);

    return (result & dirs);
}

void testPCF8574(I2cBusConnection* i2cBusConnection, OutputStream* outputStream) {
    char data;
    // PCF 0
    appendString(outputStream, "PCFADD0=");
    data = readPCF8574(i2cBusConnection, 0x40, 0, 0xFF);
    appendHex2(outputStream, data);
    delaymSec(150);
    // PCF 1
    appendString(outputStream, " PCFADD1 : ");
    data = readPCF8574(i2cBusConnection, 0x40, 1, 0xFF);
    appendHex2(outputStream, data);
    delaymSec(500);
}

// IO EXPANDER "Class"

I2cBusConnection* getIOExpanderBusConnection(IOExpander* ioExpander) {
    return (I2cBusConnection*) ioExpander->object;
}

bool ioExpanderPCF8574Init(IOExpander* ioExpander) {
    return true;
}

// SINGLE BITS

unsigned char ioExpanderPCF8574ReadValue(IOExpander* ioExpander) {
    I2cBusConnection* i2cBusConnection = getIOExpanderBusConnection(ioExpander);
    // TODO : To Change !
    return readPCF8574(i2cBusConnection, 0x40, 0x00, 0xFF);
}

void ioExpanderPCF8574WriteValue(IOExpander* ioExpander, unsigned char value) {
    I2cBusConnection* i2cBusConnection = getIOExpanderBusConnection(ioExpander);
    // TODO : To Change !
    writePCF8574(i2cBusConnection, 0x40, 0x00, 0xFF, 0x00);
}

// ALL BITS

bool ioExpanderPCF8574ReadSingleValue(IOExpander* ioExpander, unsigned int index) {
    I2cBusConnection* i2cBusConnection = getIOExpanderBusConnection(ioExpander);
    // TODO : To Change !
    return readPCF8574(i2cBusConnection, 0x40, 0x00, 0xFF);
}

void ioExpanderPCF8574WriteSingleValue(IOExpander* ioExpander, unsigned int index, bool value) {
    I2cBusConnection* i2cBusConnection = getIOExpanderBusConnection(ioExpander);
    // TODO : To Change !
    writePCF8574(i2cBusConnection, 0x40, 0x00, 0xFF, 0x00);
}

void initIOExpanderPCF8574(IOExpander* ioExpander, I2cBusConnection* i2cBusConnection) {
    initIOExpander(ioExpander,
                   &ioExpanderPCF8574Init,
                   &ioExpanderPCF8574ReadValue,
                   &ioExpanderPCF8574WriteValue,
                   &ioExpanderPCF8574ReadSingleValue,
                   &ioExpanderPCF8574WriteSingleValue,
                   8,
                   (int*) i2cBusConnection);
}