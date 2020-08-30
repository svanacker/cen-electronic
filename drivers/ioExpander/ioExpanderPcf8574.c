#include "ioExpanderPcf8574.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/io/printWriter.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "ioExpander.h"
#include "pcf8574.h"

#define PCF8574_IO_COUNT     ((unsigned int) 8)

I2cBusConnection* getIOExpanderBusConnection(IOExpander* ioExpander) {
    return (I2cBusConnection*) ioExpander->object;
}

// Forward declaration
unsigned char ioExpanderPCF8574ReadValue(IOExpander* ioExpander);

bool ioExpanderPCF8574Init(IOExpander* ioExpander) {
    I2cBusConnection* i2cBusConnection = getIOExpanderBusConnection(ioExpander);
    ioExpander->value = ioExpanderPCF8574ReadValue(ioExpander);
    return isPCF8574Present(i2cBusConnection);
}

// SINGLE BITS

unsigned char ioExpanderPCF8574ReadValue(IOExpander* ioExpander) {
    I2cBusConnection* i2cBusConnection = getIOExpanderBusConnection(ioExpander);
    unsigned char result = readPCF8574(i2cBusConnection);
    if (result != ioExpander->value) {
        ioExpander->value = result;
        if (ioExpander->ioExpanderOnValueChangeEvent != NULL) {
            ioExpander->ioExpanderOnValueChangeEvent(ioExpander, ioExpander->value, ioExpander->eventContext);
        }
    }
    return result;
}

void ioExpanderPCF8574WriteValue(IOExpander* ioExpander, unsigned char value) {
    I2cBusConnection* i2cBusConnection = getIOExpanderBusConnection(ioExpander);
    writePCF8574(i2cBusConnection, value);
    ioExpander->value = value;
}

// ALL BITS

bool ioExpanderPCF8574ReadSingleValue(IOExpander* ioExpander, unsigned int index) {
    unsigned value = ioExpanderPCF8574ReadValue(ioExpander);
    return (bool) (value & (1 << index));
}

void ioExpanderPCF8574WriteSingleValue(IOExpander* ioExpander, unsigned int index, bool value) {
    unsigned char valueToWrite;
    if (value) {
        // Set the specified bit, but keeping other value
        valueToWrite = (1 << index) | (ioExpander->value);
    } else {
        // Set the specified bit, reverts bits, and do an AND operation
        valueToWrite = (~(1UL << index)) & (ioExpander->value);
    }
    ioExpanderPCF8574WriteValue(ioExpander, valueToWrite);
}

void initIOExpanderPCF8574(IOExpander* ioExpander, const char* name, I2cBusConnection* i2cBusConnection) {
    initIOExpander(ioExpander,
            name,
            &ioExpanderPCF8574Init,
            &ioExpanderPCF8574ReadValue,
            &ioExpanderPCF8574WriteValue,
            &ioExpanderPCF8574ReadSingleValue,
            &ioExpanderPCF8574WriteSingleValue,
            PCF8574_IO_COUNT,
            (int*) i2cBusConnection);
}