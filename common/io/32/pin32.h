#ifndef PIN_32_H
#define PIN_32_H

#include <stdbool.h>

#include "../pin.h"

/**
 * Returns the name of each pin.
 * @param pinList the pinList object (POO approach)
 */
char* getPinName32(PinList* pinList, int pinIndex);

/**
 * Set the value for the pin Index (see pin.h).
 * @param pinList the encapsulation of the list of pin
 * @param the index of the pin
 * @param pinValue the new value of the pin
 */
void setPinValue32(PinList* pinList, int pinIndex, bool pinValue);

/**
 * Initializes a pin List with PIC32 Implementation.
 * @param pinList the pinList object (POO approach)
 */
void initPinList32(PinList* pinList);

#endif

