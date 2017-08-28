#ifndef PID_PERSISTENCE_H
#define PID_PERSISTENCE_H

#include <stdbool.h>

#include "../../../common/eeprom/eeprom.h"
#include "../pidMotion.h"

// -> EEPROM Index
#define EEPROM_KP                0
#define EEPROM_KI                1
#define EEPROM_KD                2
#define EEPROM_MI                3

/**
 * There are n PID structures to store with 4 values for each PID,
 * so EEPROM_PID_BLOCK_SIZE is used to store on different location.
 */
#define EEPROM_PID_BLOCK_SIZE    4

/**
 * Loads the PID data from EEPROM (or Memory which simulates Eeprom)).
 */
void loadPidParameters(PidMotion* pidMotion, bool loadDefaultValues);

/**
 * Saves the PID data to EEPROM.
 */
void savePidParameters(PidMotion* pidMotion);

#endif
