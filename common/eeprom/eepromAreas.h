#ifndef EEPROM_CONSTANTS_H
#define EEPROM_CONSTANTS_H

#include <stdbool.h>

#include "eeprom.h"

// Constant to know if the Area is Initialized or not
#define EEPROM_AREA_IS_INITIALIZED_MARKER                                 0xCCCC

// INTERNAL EEPROM
#define EEPROM_INTERNAL_AREA_MARKER_INDEX                                 0x0080
#define EEPROM_INTERNAL_START_INDEX                                       0x0082

// PID
#define EEPROM_PID_PARAMETERS_AREA_MARKER_INDEX                           0x0100
#define EEPROM_PID_PARAMETERS_START_INDEX                                 0x0102
#define EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX                   0x0182 

// MOTION
#define EEPROM_MOTION_PARAMETERS_AREA_MARKER_INDEX                        0x0200
#define EEPROM_MOTION_PARAMETERS_START_INDEX                              0x0202

// KINETICS
#define EEPROM_KINETICS_AREA_MARKER_INDEX                                 0x0300
#define EEPROM_KINETICS_START_INDEX                                       0x0302

// START MATCH
#define EEPROM_START_MATCH_AREA_MARKER_INDEX                              0x0400
#define EEPROM_START_MATCH_START_INDEX                                    0x0402

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
