#include "relayPc.h"

#include <stdbool.h>

#define RELAY_PC_COUNT 8

bool relayPcInit(Relay* relay) {
    return true;
}

bool relayPcReadValue(Relay* relay, unsigned int relayIndex) {
    unsigned int maskValue = 1 << relayIndex;
    unsigned value = *(relay->object);
    return (value & maskValue);
}

void relayPcWriteValue(Relay* relay, unsigned int relayIndex, bool value) {
    if (value) {
        // Set the bit
        *(relay->object) |= (1UL << relayIndex);
    }
    else {
        // Clear the bit
        *(relay->object) &= ~(1UL << relayIndex);
    }
}

void initRelayPc(Relay* relay, int* relayValue) {
    initRelay(relay, &relayPcInit, &relayPcReadValue, &relayPcWriteValue, RELAY_PC_COUNT, relayValue);
}
