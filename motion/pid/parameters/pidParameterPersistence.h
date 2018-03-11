#ifndef PID_PARAMETER_PERSISTENCE_H
#define PID_PARAMETER_PERSISTENCE_H

#include "../../../common/eeprom/eeprom.h"

#include "../pidMotion.h"

// -> Index in the table
#define PID_PARAMETERS_EEPROM_INDEX_KP                0
#define PID_PARAMETERS_EEPROM_INDEX_KI                1
#define PID_PARAMETERS_EEPROM_INDEX_KD                2
#define PID_PARAMETERS_EEPROM_INDEX_MI                3

/**
 * There are n PID structures to store with 4 values  (P, I, D, MI)
 */
#define EEPROM_PID_PARAMETERS_VALUE_COUNT    4

/**
 * for each PID, we needs 4 octets as we store float
 */
#define EEPROM_PID_PARAMETERS_VALUE_LENGTH   4

/**
 * Loads the PID data from EEPROM (or Memory which simulates Eeprom)).
 * @param pidMotion Stores the link to the eeprom and all pid Parameters
 * @loadDefaultValues if we load from the code the default values
 * (to initialize the first times values if Eeprom was cleared)
 */
void loadPidParameters(PidMotion* pidMotion, bool loadDefaultValues);

/**
 * Saves the PID data to EEPROM.
 * @param pidMotion Stores the link to the eeprom and all pid Parameters
 */
void savePidParameters(PidMotion* pidMotion);

#endif
