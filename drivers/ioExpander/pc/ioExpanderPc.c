#include "ioExpanderPc.h"

#include <stdbool.h>

#define IO_EXPANDER_BIT_COUNT 8

bool ioExpanderPcInit(IOExpander* ioExpander) {
    return true;
}

bool ioExpanderPcReadValue(IOExpander* ioExpander, int ioIndex) {
    unsigned int maskValue = 1 << ioIndex;
    unsigned value = *(ioExpander->object);
    return (value & maskValue);
}

void ioExpanderPcWriteValue(IOExpander* ioExpander, int ioIndex, bool value) {
    if (value) {
        // Set the bit
        *(ioExpander->object) |= (1UL << ioIndex);
    }
    else {
        // Clear the bit
        *(ioExpander->object) &= ~(1UL << ioIndex);
    }
}

void initIOExpanderPc(IOExpander* ioExpander, int* ioExpanderValue) {
    initIOExpander(ioExpander, &ioExpanderPcInit, &ioExpanderPcReadValue, &ioExpanderPcWriteValue, IO_EXPANDER_BIT_COUNT, ioExpanderValue);
}
