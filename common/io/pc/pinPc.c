#include "pinPc.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../pin.h"

static bool pinValuesPc[PIN_MAX_INDEX + 1];

bool getPinValuePc(PinList* pinList, int pinIndex) {
    return pinValuesPc[pinIndex];
}

void setPinValuePc(PinList* pinList, int pinIndex, bool pinValue) {
    pinValuesPc[pinIndex] = pinValue;
}

/**
 * Initialise a pin List for Pc.
 * @param pinList pointer on pinList object (POO Paradigm)
 */
void initPinListPc(PinList* pinList) {
    initPinList(pinList, &getPinValuePc, &setPinValuePc, NULL);
}
