#include "pidPersistence.h"

#include <stdlib.h>

#include "../pid.h"

#include "../../../common/commons.h"
#include "../../../common/eeprom/eeprom.h"
#include "../../../common/eeprom/eepromAreas.h"
#include "../../../common/error/error.h"

// DEFAULT VALUES : As the PID value is stored into the eeprom, this will be erased by 
// Programming. It's very dangerous if we forget to send default values

// For 5000 impulsions coders
#define PID_STORED_COUNT        8
static signed int DEFAULT_EEPROM_VALUES[EEPROM_PID_START_INDEX + (EEPROM_PID_BLOCK_SIZE * PID_STORED_COUNT)] ={
    // RESERVED area for EEPROM
    0x00,
    // NORMAL VALUES
    // Go (P I D MI)
    0x20, 0x00, 0x30, 0x00,
    0x40, 0x00, 0x30, 0x00,
    // Rotation (P I D MI)
    0x40, 0x00, 0x30, 0x00,
    0x40, 0x00, 0x30, 0x00,
    // Maintain Position
    0x7E, 0x00, 0x7E, 0x00,
    0x7E, 0x00, 0x7E, 0x00,
    // Adjust to the border : it needs small Alpha PID to be able to adjust to the border
    0x20, 0x00, 0x30, 0x00,
    0x05, 0x00, 0x30, 0x00,
};

// Values not stored into the EEPROM
#define ROLLING_TEST_P                0x10
#define ROLLING_TEST_I                0x00
#define ROLLING_TEST_D                0x10
#define ROLLING_TEST_MAX_INTEGRAL    0x10

#define END_APPROACH_P                0x7D
#define END_APPROACH_I                0x00
#define END_APPROACH_D                0x7D
#define END_APPROACH_MAX_INTEGRAL    0x00

// Not used
#define DEFAULT_MAX_INTEGRAL 0

static Eeprom* pidPersistenceEeprom;

/**
 * Returns the real data Index in storage area for a specific pid and a specific value
 * @param pidIndex the index of PID (between 0 and PID_COUNT)
 * @param dataIndex the index of data (between 0 and EEPROM_PID_BLOCK_SIZE)
 */
unsigned char getRealDataIndex(unsigned pidIndex, unsigned int dataIndex) {
    unsigned result = EEPROM_PID_START_INDEX + ((pidIndex * EEPROM_PID_BLOCK_SIZE) + dataIndex);
    return result;
}

/**
 * Store a pid Parameter
 * @param pidIndex the index of PID (between 0 and PID_COUNT)
 * @param dataIndex the index of data (between 0 and EEPROM_PID_BLOCK_SIZE)
 * @param value the value to store
 */
void internalSavePidParameter(unsigned pidIndex, unsigned int dataIndex, signed int value) {
    if (pidPersistenceEeprom == NULL) {
        writeError(PID_PERSISTENCE_NO_EEPROM);
        return;
    }
    unsigned realIndex = getRealDataIndex(pidIndex, dataIndex);
	// TODO : char / int problem
    pidPersistenceEeprom->eepromWriteChar(pidPersistenceEeprom, realIndex, value);
}

/**
 * @param pidIndex the index of PID (between 0 and 3)
 * @param dataIndex the index of data (between 0 and EEPROM_PID_BLOCK_SIZE)
 * @return value the value to load
 */
signed int internalLoadPidParameter(unsigned pidIndex, unsigned int dataIndex, bool loadDefaultValue) {
    if (pidPersistenceEeprom == NULL) {
        writeError(PID_PERSISTENCE_NO_EEPROM);
        return 0;
    }
    unsigned realIndex = getRealDataIndex(pidIndex, dataIndex);

    unsigned char result;
	// TODO : char / int problem
    if (loadDefaultValue) {
        result = DEFAULT_EEPROM_VALUES[realIndex];
    }
    else {
    	bool pidParametersEepromAreaIsInitialized = isEepromAreaInitialized(pidPersistenceEeprom, EEPROM_PID_AREA_MARKER_INDEX);
    	if (!pidParametersEepromAreaIsInitialized) {
    		writeError(PID_PERSISTENCE_EEPROM_NOT_INITIALIZED);
    		return 0;
    	}
        result = pidPersistenceEeprom->eepromReadChar(pidPersistenceEeprom, realIndex);
    }
    return result;
}

/**
 * Load the PID Parameters of the Eeprom into Memory.
 */
void loadPidParameters(bool loadDefaultValue) {
    int pidIndex;
    for (pidIndex = 0; pidIndex < PID_STORED_COUNT; pidIndex++) {
        Pid* localPid = getPID(pidIndex, 0);
        localPid->p = (float) internalLoadPidParameter(pidIndex, EEPROM_KP, loadDefaultValue);
        localPid->i = (float) internalLoadPidParameter(pidIndex, EEPROM_KI, loadDefaultValue);
        localPid->d = (float) internalLoadPidParameter(pidIndex, EEPROM_KD, loadDefaultValue);
        localPid->maxIntegral = (float) internalLoadPidParameter(pidIndex, EEPROM_MI, loadDefaultValue);
        localPid->enabled = true;
    }

    // Load rolling Test parameters
    /*
    Pid* rollingTestModePid = getPID(ROLLING_TEST);
    rollingTestModePid->p = ROLLING_TEST_P;
    rollingTestModePid->i = ROLLING_TEST_I;
    rollingTestModePid->d = ROLLING_TEST_D;
    rollingTestModePid->maxIntegral = ROLLING_TEST_MAX_INTEGRAL;
    rollingTestModePid->derivativePeriod = DEFAULT_DERIVATIVE_PERIOD;
    rollingTestModePid->enabled = true;
     */

    // Parameter for End of trajectory
    int instructionIndex = 0;
    // For Alpha / Theta
    for (instructionIndex = 0; instructionIndex < INSTRUCTION_COUNT; instructionIndex++) {
        pidIndex = getIndexOfPid(instructionIndex, PID_TYPE_FINAL_APPROACH_INDEX);
        Pid* endApproachPid = getPID(pidIndex, 0);
        endApproachPid->p = END_APPROACH_P;
        endApproachPid->i = END_APPROACH_I;
        endApproachPid->d = END_APPROACH_D;
        endApproachPid->maxIntegral = END_APPROACH_MAX_INTEGRAL;
        endApproachPid->enabled = true;
    }
}

/**
 * Save the parameters of the PID into Eeprom.
 */
void savePidParameters(void) {
	initEepromArea(pidPersistenceEeprom, EEPROM_PID_AREA_MARKER_INDEX);
    int pidIndex;
    // we save both NORMAL_MODE AND ROLLING_TEST_MODE
    for (pidIndex = 0; pidIndex < PID_STORED_COUNT; pidIndex++) {
        Pid* localPid = getPID(pidIndex, 0);
        internalSavePidParameter(pidIndex, EEPROM_KP, (int) localPid->p);
        internalSavePidParameter(pidIndex, EEPROM_KI, (int) localPid->i);
        internalSavePidParameter(pidIndex, EEPROM_KD, (int) localPid->d);
        internalSavePidParameter(pidIndex, EEPROM_MI, (int) localPid->maxIntegral);
    }
}

void initPidPersistence(Eeprom* eeprom_) {
    pidPersistenceEeprom = eeprom_;
}

