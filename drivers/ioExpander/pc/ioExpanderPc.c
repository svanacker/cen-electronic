#include "ioExpanderPc.h"

#include <stdbool.h>

#define IO_EXPANDER_BIT_COUNT 8

bool ioExpanderPcInit(IOExpander* ioExpander) {
    return true;
}

// ALL BITS

unsigned char ioExpanderPcReadValue(IOExpander* ioExpander) {
    unsigned int value = *(ioExpander->object);
    return (unsigned char) (value);
}

void ioExpanderPcWriteValue(IOExpander* ioExpander, unsigned char value) {
    int valueToStore = (unsigned int) value;
    *(ioExpander->object) = valueToStore;
}

// SINGLE BIT

bool ioExpanderPcReadSingleValue(IOExpander* ioExpander, unsigned int ioIndex) {
    unsigned int maskValue = 1 << ioIndex;
    unsigned value = *(ioExpander->object);
    return (value & maskValue);
}

void ioExpanderPcWriteSingleValue(IOExpander* ioExpander, unsigned int ioIndex, bool value) {
    if (value) {
        // Set the bit
        *(ioExpander->object) |= (1UL << ioIndex);
    } else {
        // Clear the bit
        *(ioExpander->object) &= ~(1UL << ioIndex);
    }
}

void initIOExpanderPc(IOExpander* ioExpander, int* ioExpanderValue) {
    initIOExpander(ioExpander,
            &ioExpanderPcInit,
            &ioExpanderPcReadValue,
            &ioExpanderPcWriteValue,
            &ioExpanderPcReadSingleValue,
            &ioExpanderPcWriteSingleValue,
            IO_EXPANDER_BIT_COUNT,
            ioExpanderValue);
}
