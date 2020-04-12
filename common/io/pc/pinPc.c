#include "pinPc.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../pin.h"

static bool pinValuesPc[PIN_MAX_INDEX + 1];
static bool pinInputValuesPc[PIN_MAX_INDEX + 1];

bool isPinValidPc(PinList* pinList, int pinIndex) {
    return pinIndex >= PIN_MIN_INDEX && pinIndex <= PIN_MAX_INDEX;
}

bool isPinInputPc(PinList* pinList, int pinIndex) {
    return pinInputValuesPc[pinIndex];
}

void setPinInputPc(PinList* pinList, int pinIndex, bool input) {
    pinInputValuesPc[pinIndex] = input;
}

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
    initPinList(pinList, &isPinValidPc, &isPinInputPc, &setPinInputPc, &getPinValuePc, &setPinValuePc, NULL);
}
