#include "multiplexer.h"

void initMultiplexer(Multiplexer* multiplexer,
                    MultiplexerInitFunction* multiplexerInit,
                    MultiplexerReadChannelsMaskFunction* multiplexerReadChannelsMask,
                    MultiplexerWriteChannelsMaskFunction* multiplexerWriteChannelsMask,
                    MultiplexerGetChannelEnableFunction* multiplexerGetChannelEnable,
                    MultiplexerSetChannelEnableFunction* multiplexerSetChannelEnable,
                   unsigned int channelCount,
                   int* object) {
    multiplexer->multiplexerInit = multiplexerInit;
    multiplexer->multiplexerReadChannelsMask = multiplexerReadChannelsMask;
    multiplexer->multiplexerWriteChannelsMask = multiplexerWriteChannelsMask;
    multiplexer->multiplexerGetChannelEnable = multiplexerGetChannelEnable;
    multiplexer->multiplexerSetChannelEnable = multiplexerSetChannelEnable;
    multiplexer->channelCount = channelCount;
    multiplexer->object = object;
}
