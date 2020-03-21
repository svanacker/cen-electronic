#ifndef MULTIPLEXER_H
#define MULTIPLEXER_H

#include <stdbool.h>

// forward declaration
struct Multiplexer;
typedef struct Multiplexer Multiplexer;

#define MULTIPLEXER_CHANNEL_0                 0
#define MULTIPLEXER_CHANNEL_1                 1
#define MULTIPLEXER_CHANNEL_2                 2
#define MULTIPLEXER_CHANNEL_3                 3
#define MULTIPLEXER_CHANNEL_4                 4
#define MULTIPLEXER_CHANNEL_5                 5
#define MULTIPLEXER_CHANNEL_6                 6
#define MULTIPLEXER_CHANNEL_7                 7


/**
 * Type of function to Multiplexer.
 */
typedef bool MultiplexerInitFunction(Multiplexer* multiplexer);

// ALL CHANNELS at the same time

/**
 * Read the channels configuration masks (which ables to redirect the input 
 * traffic to 0 to n channels 
 * @return the value of the Multiplexer Channels Mask
 */
typedef unsigned char MultiplexerReadChannelsMaskFunction(Multiplexer* multiplexer);

/**
 * Write the mask with the channels mask.
 */
typedef void MultiplexerWriteChannelsMaskFunction(Multiplexer* multiplexer, unsigned char value);

// SINGLE CHANNEL

/**
 * Read if the specified channel is on or off for the specified channelIndex
 * @return true if the channel specified by the channel index is enable or not
 */
typedef bool MultiplexerGetChannelEnableFunction(Multiplexer* multiplexer, unsigned int channelIndex);

/**
 * Write a specific channel to redirect or not for the specified channelIndex.
 */
typedef void MultiplexerSetChannelEnableFunction(Multiplexer* multiplexer, unsigned int channelIndex, bool value);

/**
 * Defines the contract Multiplexer like the TCA9548A.
 */
struct Multiplexer {
    MultiplexerInitFunction* multiplexerInit;
    MultiplexerReadChannelsMaskFunction* multiplexerReadChannelsMask;
    MultiplexerWriteChannelsMaskFunction* multiplexerWriteChannelsMask;
    MultiplexerGetChannelEnableFunction* multiplexerGetChannelEnable;
    MultiplexerSetChannelEnableFunction* multiplexerSetChannelEnable;
    /** How many Channel are managed .*/
    unsigned int channelCount;
    /** Last value (must not be handled by external systems) */
    unsigned int _lastChannelsMask;
    /** Do we use a cache to avoid sending always lots of I2c command if we use the configure always the same channelMasks */
    bool useChannelMasksCache;
    /** pointer on other object (useful for I2C Connection for example) .*/
    int* object;
};

/** 
 * Init the wrapper around the Multiplexer. 
 */
void initMultiplexer(Multiplexer* multiplexer,
        MultiplexerInitFunction* multiplexerInit,
        MultiplexerReadChannelsMaskFunction* multiplexerReadChannelsMask,
        MultiplexerWriteChannelsMaskFunction* multiplexerWriteChannelsMask,
        MultiplexerGetChannelEnableFunction* multiplexerGetChannelEnable,
        MultiplexerSetChannelEnableFunction* multiplexerSetChannelEnable,
        unsigned int channelCount,
        bool useChannelMasksCache,
        int* object);

// UTILS FUNCTION

/**
 * Activate a specific channel and disable all others !
 * @param multiplexer
 * @param channelIndex
 */
void multiplexerEnableOnly(Multiplexer* multiplexer, unsigned int channelIndex);


void multiplexerDisableAll(Multiplexer* multiplexer);

void multiplexerEnableAll(Multiplexer* multiplexer);

#endif
