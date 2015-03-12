#ifndef EEPROM_CONSTANTS_H
#define EEPROM_CONSTANTS_H

#include <stdbool.h>

#include "eeprom.h"

// Constant to know if the Area is Initialized or not
#define EEPROM_AREA_IS_INITIALIZED_MARKER			0xCCCC

// PID
#define EEPROM_PID_AREA_MARKER_INDEX				0x0100
#define EEPROM_PID_START_INDEX						0x0102

// MOTION
#define EEPROM_MOTION_AREA_MARKER_INDEX				0x0200
#define EEPROM_MOTION_START_INDEX					0x0202

// KINETICS
#define EEPROM_KINETICS_AREA_MARKER_INDEX			0x0300
#define EEPROM_KINETICS_START_INDEX					0x0302

/**
 * Returns true if the area is initialized. A marker must be written at the two first character to consider it as initialized
 * @param eeprom_ the eeprom object
 * @param initiazedAreaIndex the base index for the area
 * @return true if the two chars are the right constant indicates that it's ok, false else
 */
bool isEepromAreaInitialized(Eeprom* eeprom_, unsigned long initiazedAreaIndex);

/**
 * Initialized an area with a marker at the beginning of characters.
 * This is very useful to know if some data exists in the area, especially if the eeprom is cleaned or changed.
 */
void initEepromArea(Eeprom* eeprom_, unsigned long initiazedAreaIndex);

#endif
