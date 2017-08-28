#include "pidPersistence.h"

#include <stdlib.h>

#include "../pid.h"
#include "../parameters/pidParameter.h"

#include "../../../common/commons.h"
#include "../../../common/eeprom/eeprom.h"
#include "../../../common/eeprom/eepromAreas.h"
#include "../../../common/error/error.h"

// DEFAULT VALUES : As the PID value is stored into the eeprom, this will be erased by 
// Programming. It's very dangerous if we forget to send default values

// For 5000 impulsions coders
#define PID_STORED_COUNT        8
static signed int DEFAULT_EEPROM_VALUES[EEPROM_PID_BLOCK_SIZE * PID_STORED_COUNT] = {
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

/**
 * Returns the real data Index in storage area for a specific pid and a specific value
 * @param pidIndex the index of PID (between 0 and PID_COUNT)
 * @param dataIndex the index of data (between 0 and EEPROM_PID_BLOCK_SIZE)
 */
unsigned int getRealDataIndex(unsigned int pidIndex, unsigned int dataIndex) {
    unsigned int result = (pidIndex * EEPROM_PID_BLOCK_SIZE) + dataIndex;
    return result;
}

/**
 * Store a pid Parameter
 * @param pidIndex the index of PID (between 0 and PID_COUNT)
 * @param dataIndex the index of data (between 0 and EEPROM_PID_BLOCK_SIZE)
 * @param value the value to store
 */
void internalSavePidParameter(PidMotion* pidMotion, unsigned int pidIndex, unsigned int dataIndex, signed int value) {
	Eeprom* _eeprom = pidMotion->pidPersistenceEeprom;
    if (_eeprom == NULL) {
        writeError(PID_PERSISTENCE_NO_EEPROM);
        return;
    }
    unsigned realIndex = getRealDataIndex(pidIndex, dataIndex);
	_eeprom->eepromWriteChar(_eeprom, EEPROM_PID_START_INDEX + realIndex, value);
}

/**
 * @param pidIndex the index of PID (between 0 and 3)
 * @param dataIndex the index of data (between 0 and EEPROM_PID_BLOCK_SIZE)
 * @return value the value to load
 */
signed int internalLoadPidParameter(PidMotion* pidMotion, unsigned int pidIndex, unsigned int dataIndex, bool loadDefaultValue) {
	Eeprom* _eeprom = pidMotion->pidPersistenceEeprom;
    if (_eeprom == NULL) {
        writeError(PID_PERSISTENCE_NO_EEPROM);
        return 0;
    }
    unsigned int realIndex = getRealDataIndex(pidIndex, dataIndex);

    unsigned char result;
    if (loadDefaultValue) {
        result = DEFAULT_EEPROM_VALUES[realIndex];
    }
    else {
        bool pidParametersEepromAreaIsInitialized = isEepromAreaInitialized(_eeprom, EEPROM_PID_AREA_MARKER_INDEX);
        if (!pidParametersEepromAreaIsInitialized) {
            writeError(PID_PERSISTENCE_EEPROM_NOT_INITIALIZED);
            return 0;
        }
        result = _eeprom->eepromReadChar(_eeprom, EEPROM_PID_START_INDEX + realIndex);
    }
    return result;
}

/**
 * Load the PID Parameters of the Eeprom into Memory.
 */
void loadPidParameters(PidMotion* pidMotion, bool loadDefaultValue) {
    int pidIndex;
    for (pidIndex = 0; pidIndex < PID_STORED_COUNT; pidIndex++) {
        PidParameter* localPidParameter = getPidParameter(pidMotion, pidIndex, 0);
        localPidParameter->p = (float)internalLoadPidParameter(pidMotion, pidIndex, EEPROM_KP, loadDefaultValue);
        localPidParameter->i = (float)internalLoadPidParameter(pidMotion, pidIndex, EEPROM_KI, loadDefaultValue);
        localPidParameter->d = (float)internalLoadPidParameter(pidMotion, pidIndex, EEPROM_KD, loadDefaultValue);
        localPidParameter->maxIntegral = (float)internalLoadPidParameter(pidMotion, pidIndex, EEPROM_MI, loadDefaultValue);
        localPidParameter->enabled = true;
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
    enum InstructionType instructionType;
    // For Alpha / Theta
    for (instructionType = 0; instructionType < INSTRUCTION_COUNT; instructionType++) {
        pidIndex = getIndexOfPid(instructionType, PID_TYPE_FINAL_APPROACH_INDEX);
        PidParameter* endApproachPidParameter = getPidParameter(pidMotion, pidIndex, 0);
        endApproachPidParameter->p = END_APPROACH_P;
        endApproachPidParameter->i = END_APPROACH_I;
        endApproachPidParameter->d = END_APPROACH_D;
        endApproachPidParameter->maxIntegral = END_APPROACH_MAX_INTEGRAL;
        endApproachPidParameter->enabled = true;
    }
}

/**
 * Save the parameters of the PID into Eeprom.
 */
void savePidParameters(PidMotion* pidMotion) {
    initEepromArea(pidMotion->pidPersistenceEeprom, EEPROM_PID_AREA_MARKER_INDEX);
    int pidIndex;
    // we save both NORMAL_MODE AND ROLLING_TEST_MODE
    for (pidIndex = 0; pidIndex < PID_STORED_COUNT; pidIndex++) {
        PidParameter* localPidParameter = getPidParameter(pidMotion, pidIndex, 0);
        internalSavePidParameter(pidMotion, pidIndex, EEPROM_KP, (int) localPidParameter->p);
        internalSavePidParameter(pidMotion, pidIndex, EEPROM_KI, (int) localPidParameter->i);
        internalSavePidParameter(pidMotion, pidIndex, EEPROM_KD, (int) localPidParameter->d);
        internalSavePidParameter(pidMotion, pidIndex, EEPROM_MI, (int) localPidParameter->maxIntegral);
    }
}

