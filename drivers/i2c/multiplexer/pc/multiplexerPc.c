#include "multiplexerPc.h"

#include <stdbool.h>

#define MULTIPLEXER_CHANNEL_COUNT         8

bool multiplexerPcInit(Multiplexer* multiplexer) {
    return true;
}

// ALL BITS

unsigned char multiplexerPcReadChannelsMask(Multiplexer* multiplexer) {
    unsigned int value = *(multiplexer->object);
    return (unsigned char) (value);
}

void multiplexerPcWriteChannelsMask(Multiplexer* multiplexer, unsigned char value) {
    int valueToStore = (unsigned int) value;
    *(multiplexer->object) = valueToStore;
}

// SINGLE BIT

bool multiplexerPcReadGetChannelEnable(Multiplexer* multiplexer, unsigned int channelIndex) {
    unsigned int maskValue = 1 << channelIndex;
    unsigned value = *(multiplexer->object);
    return (value & maskValue);
}

void multiplexerPcSetChannelEnable(Multiplexer* multiplexer, unsigned int channelIndex, bool value) {
    if (value) {
        // Set the bit
        *(multiplexer->object) |= (1UL << channelIndex);
    }
    else {
        // Clear the bit
        *(multiplexer->object) &= ~(1UL << channelIndex);
    }
}

void initMultiplexerPc(Multiplexer* multiplexer, int* multiplexerValue) {
    initMultiplexer(multiplexer, 
                   &multiplexerPcInit,
                   &multiplexerPcReadChannelsMask,
                   &multiplexerPcWriteChannelsMask,
                   &multiplexerPcReadGetChannelEnable,
                   &multiplexerPcSetChannelEnable,
                   MULTIPLEXER_CHANNEL_COUNT,
                   true,
                   multiplexerValue);
}
