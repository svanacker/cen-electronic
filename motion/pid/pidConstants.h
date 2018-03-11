#ifndef PID_CONSTANTS_H
#define PID_CONSTANTS_H

#include "instructionType.h"
#include "pidType.h"

// PID CONSTANT

/** How many Item of PID Computation Values we store */
#define PID_HISTORY_ITEM_COUNT                                              1000

/**
 * Defines the error for which we apply strong PID and not normal PID.
 */
// TODO : Use a parameter in Eeprom
#define ERROR_FOR_STRONG_PID                     20

/**
 * Defines the number of pid interrupt after the end (t3) to apply strong PID.
 */
// TODO : Use a parameter in Eeprom
#define TIME_PERIOD_AFTER_END_FOR_STRONG_PID     40

#endif