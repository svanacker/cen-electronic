#include "multiplexer.h"

#include <stdbool.h>

void initMultiplexer(Multiplexer* multiplexer,
                    MultiplexerInitFunction* multiplexerInit,
                    MultiplexerReadChannelsMaskFunction* multiplexerReadChannelsMask,
                    MultiplexerWriteChannelsMaskFunction* multiplexerWriteChannelsMask,
                    MultiplexerGetChannelEnableFunction* multiplexerGetChannelEnable,
                    MultiplexerSetChannelEnableFunction* multiplexerSetChannelEnable,
                   unsigned int channelCount,
                   bool useChannelMasksCache,
                   int* object) {
    multiplexer->multiplexerInit = multiplexerInit;
    multiplexer->multiplexerReadChannelsMask = multiplexerReadChannelsMask;
    multiplexer->multiplexerWriteChannelsMask = multiplexerWriteChannelsMask;
    multiplexer->multiplexerGetChannelEnable = multiplexerGetChannelEnable;
    multiplexer->multiplexerSetChannelEnable = multiplexerSetChannelEnable;
    multiplexer->channelCount = channelCount;
    multiplexer->useChannelMasksCache = useChannelMasksCache;
    multiplexer->object = object;
}

void multiplexerDisableAll(Multiplexer* multiplexer) {
    multiplexer->multiplexerWriteChannelsMask(multiplexer, 0x00);
}

void multiplexerEnableAll(Multiplexer* multiplexer) {
    multiplexer->multiplexerWriteChannelsMask(multiplexer, 0xFF);
}

void multiplexerEnableOnly(Multiplexer* multiplexer, unsigned int channelIndex) {
    multiplexer->multiplexerWriteChannelsMask(multiplexer, 1 << channelIndex);
}