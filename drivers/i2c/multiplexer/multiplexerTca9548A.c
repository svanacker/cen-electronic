#include "multiplexerTca9548A.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../../common/io/printWriter.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "multiplexer.h"
#include "tca9548A.h"

#define TCA9548A_CHANNEL_COUNT     ((unsigned int) 8)

I2cBusConnection* getMultiplexerI2cBusConnection(Multiplexer* multiplexer) {
    return (I2cBusConnection*) multiplexer->object;
}

// Forward declaration
unsigned char multiplexerTca9548AReadChannelsMask(Multiplexer* multiplexer);

bool multiplexerTca9548AInit(Multiplexer* multiplexer) {
    multiplexer->_lastChannelsMask = multiplexerTca9548AReadChannelsMask(multiplexer);

    // TODO : How to know if it's ok ?
    return true;
}

// ALL BITS at SAME TIME

unsigned char multiplexerTca9548AReadChannelsMask(Multiplexer* multiplexer) {
    I2cBusConnection* i2cBusConnection = getMultiplexerI2cBusConnection(multiplexer);
    unsigned char result = tca9548A_getChannelsMask (i2cBusConnection);
    multiplexer->_lastChannelsMask = result;
    return result;
}

void multiplexerTca9548AWriteChannelsMask(Multiplexer* multiplexer, unsigned char channelsMask) {
    I2cBusConnection* i2cBusConnection = getMultiplexerI2cBusConnection(multiplexer);
    if (multiplexer->useChannelMasksCache) {
        // We write into the channel ONLY if the new value is different
        if (channelsMask != multiplexer->_lastChannelsMask) {
            tca9548A_setChannelsMask(i2cBusConnection, channelsMask);
        }
    }
    else {
        tca9548A_setChannelsMask(i2cBusConnection, channelsMask);
        
    }
    multiplexer->_lastChannelsMask = channelsMask;
}

// SINGLE BITS
bool multiplexerTca9548AGetChannelEnable(Multiplexer* multiplexer, unsigned int index) {
    unsigned char value = multiplexerTca9548AReadChannelsMask(multiplexer);
    return (bool) (value & (1 << index));
}

void multiplexerTca9548A4SetChannelEnable(Multiplexer* multiplexer, unsigned int index, bool value) {
    unsigned char valueToWrite;
    if (value) {
        // Set the specified bit, but keeping other value
        valueToWrite = (1 << index) | (multiplexer->_lastChannelsMask);
    }
    else {
        // Set the specified bit, reverts bits, and do an AND operation
        valueToWrite = (~(1UL << index)) & (multiplexer->_lastChannelsMask);
    }
    multiplexerTca9548AWriteChannelsMask(multiplexer, valueToWrite);  
}

void initMultiplexerTca9548A(Multiplexer* multiplexer, I2cBusConnection* i2cBusConnection, bool useChannelMasksCache) {
    initMultiplexer(multiplexer,
                   &multiplexerTca9548AInit,
                   &multiplexerTca9548AReadChannelsMask,
                   &multiplexerTca9548AWriteChannelsMask,
                   &multiplexerTca9548AGetChannelEnable,
                   &multiplexerTca9548A4SetChannelEnable,
                   TCA9548A_CHANNEL_COUNT,
                   useChannelMasksCache,
                   (int*) i2cBusConnection);
}