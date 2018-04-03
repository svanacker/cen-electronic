#include "ioExpanderPcf8574.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "ioExpander.h"

#define PCF8574_IO_COUNT     ((unsigned int) 8)

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