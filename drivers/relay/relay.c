#include "relay.h"

void initRelay(Relay* relay,
        relayInitFunction* relayInit,
        relayReadValueFunction* relayReadValue,
        relayWriteValueFunction* relayWriteValue,
        unsigned int count,
        int* object) {
    relay->relayInit = relayInit;
    relay->relayReadValue = relayReadValue;
    relay->relayWriteValue = relayWriteValue;
    relay->count = count;
    relay->object = object;
}