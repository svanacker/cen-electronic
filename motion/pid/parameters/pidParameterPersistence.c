#include "pidParameterPersistence.h"

#include <stdlib.h>

#include "../pid.h"
#include "../parameters/pidParameter.h"
#include "../endDetection/parameters/motionEndDetectionParameterPersistence.h"
#include "../../../common/commons.h"
#include "../../../common/eeprom/eeprom.h"
#include "../../../common/eeprom/eepromAreas.h"
#include "../../../common/error/error.h"

static float PID_PARAMETERS_EEPROM_DEFAULT_VALUES[EEPROM_PID_PARAMETERS_VALUE_COUNT * PID_TYPE_COUNT] = {
    // PID_TYPE_NONE
    0.0f, 0.0f, 0.0f, 0.0f,
    // PID_TYPE_GO_INDEX
    3.0f, 0.0f, 25.6f, 0.0f,
    // PID_TYPE_ROTATE_INDEX
    3.0f, 0.0f, 25.6f, 0.0f,
    // PID_TYPE_FINAL_APPROACH
    3.0f, 0.0f, 25.6f, 0.0f,
    // PID_TYPE_MAINTAIN_POSITION_INDEX
    5.0f, 0.0f, 51.2f, 0.0f,
    // PID_TYPE_ADJUST
    1.0f, 0.0f, 1.0f, 0.0f
};

// EEPROM CHECK

/**
 * Check if the eeprom is initialized inside the pidMotion structure
 * @param pidMotion the pidMotion containing the eeprom reference object
 * @return 
 */
bool internalPidParametersCheckIfEepromIsNotNull(PidMotion* pidMotion) {
    Eeprom* _eeprom = pidMotion->pidPersistenceEeprom;
    if (_eeprom == NULL) {
        writeError(PID_PARAMETERS_PERSISTENCE_NO_EEPROM);
        return false;
    }
    return true;
}

/**
 * Check if the eeprom is initialized with the right marker (to be sure that
 * the eeprom is really ok, and not return always the same values)
 * @param _eeprom the eeprom object structure
 * @return 
 */
bool internalPidParametersCheckIfEepromIsInitialized(Eeprom* _eeprom) {
    bool pidParametersEepromAreaIsInitialized = isEepromAreaInitialized(_eeprom, EEPROM_PID_PARAMETERS_AREA_MARKER_INDEX);
    if (!pidParametersEepromAreaIsInitialized) {
        writeError(PID_PARAMETERS_PERSISTENCE_EEPROM_NOT_INITIALIZED);
        return false;
    }
    return true;
}

// PID PARAMETER UNIT GET / SET

/**
 * @private
 * Returns the real data Index in storage area for a specific pid and a specific value
 * @param pidIndex the index of PID (between 0 and PID_TYPE_COUNT)
 * @param dataIndex the index of data (between 0 and EEPROM_PID_PARAMETERS_VALUE_COUNT)
 */
unsigned int getPidParameterPersistenceRealDataIndex(unsigned int pidIndex, unsigned int dataIndex) {
    unsigned int result = (pidIndex * EEPROM_PID_PARAMETERS_VALUE_COUNT) + dataIndex;
    return result;
}

/**
 * @private
 * Store a pid Parameter.
 * Load a complete PidParameter structure. We do not check if eeprom is properly
 * initialized, this is the responsability of the caller of this method
 * @param pidIndex the index of PID (between 0 and PID_COUNT)
 * @param dataIndex the index of data (between 0 and EEPROM_PID_BLOCK_SIZE)
 * @param value the value to store
 */
void internalSavePidParameter(PidMotion* pidMotion, unsigned int pidIndex, unsigned int dataIndex, float value) {
    unsigned int realIndex = getPidParameterPersistenceRealDataIndex(pidIndex, dataIndex);
    Eeprom* _eeprom = pidMotion->pidPersistenceEeprom;
    // Compute the real index
    unsigned long realDataEepromIndex = EEPROM_PID_PARAMETERS_START_INDEX + (realIndex * EEPROM_PID_PARAMETERS_VALUE_LENGTH);
	eepromWriteUnsignedFloat (_eeprom, realDataEepromIndex, value, PID_VALUE_DIGIT_PRECISION);
}


/**
 * @private
 * Load a complete PidParameter structure. We do not check if eeprom is properly
 * initialized, this is the responsability of the caller of this method
 * @param pidIndex the index of PID (between 0 and 3)
 * @param dataIndex the index of data (between 0 and EEPROM_PID_BLOCK_SIZE)
 * @return value the value to load
 */
float internalLoadPidParameter(PidMotion* pidMotion, unsigned int pidIndex, unsigned int dataIndex, bool loadDefaultValue) {
    unsigned int realIndex = getPidParameterPersistenceRealDataIndex(pidIndex, dataIndex);

    float result;
    if (loadDefaultValue) {
        result = PID_PARAMETERS_EEPROM_DEFAULT_VALUES[realIndex];
    }
    else {
        Eeprom* _eeprom = pidMotion->pidPersistenceEeprom;
        unsigned long realDataEepromIndex = EEPROM_PID_PARAMETERS_START_INDEX + (realIndex * EEPROM_PID_PARAMETERS_VALUE_LENGTH);
        result = eepromReadUnsignedFloat(_eeprom, realDataEepromIndex, PID_VALUE_DIGIT_PRECISION);
    }
    return result;
}

// INTERFACE FUNCTIONS

void loadPidParameters(PidMotion* pidMotion, bool loadDefaultValues) {
    // If we must take values from the eeprom, we check if the eeprom 
    // is not null and is initialized
    if (!loadDefaultValues) {
        if (!internalPidParametersCheckIfEepromIsNotNull(pidMotion)) {
            return;
        }
        if (!internalPidParametersCheckIfEepromIsInitialized(pidMotion->pidPersistenceEeprom)) {
            return;
        }
    }
    unsigned int pidIndex;
    unsigned int pidTypeCount = getPidTypeCount();
    for (pidIndex = 0; pidIndex < pidTypeCount; pidIndex++) {
        PidParameter* localPidParameter = getPidParameterByIndex(pidMotion, pidIndex);
        localPidParameter->p = internalLoadPidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_KP, loadDefaultValues);
        localPidParameter->i = internalLoadPidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_KI, loadDefaultValues);
        localPidParameter->d = internalLoadPidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_KD, loadDefaultValues);
        localPidParameter->maxIntegral = internalLoadPidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_MI, loadDefaultValues);
        localPidParameter->enabled = true;
    }
    
    // Load Motion End Detection Parameter : detail Phase And Aggregation Phase
    MotionEndDetectionParameter* motionEndDetectionParameter = &(pidMotion->globalParameters.motionEndDetectionParameter);
    loadMotionEndDetectionParameters(motionEndDetectionParameter, pidMotion->pidPersistenceEeprom, loadDefaultValues);
}

void savePidParameters(PidMotion* pidMotion) {
    if (!internalPidParametersCheckIfEepromIsNotNull(pidMotion)) {
        return;
    }
    // Initializes the AREA to declare the Eeprom Area Initialized
    initEepromArea(pidMotion->pidPersistenceEeprom, EEPROM_PID_PARAMETERS_AREA_MARKER_INDEX);

    // Store All Pid Parameters (P, I, D, MI)
    int pidIndex;
    // we save both NORMAL_MODE AND ROLLING_TEST_MODE
    for (pidIndex = 0; pidIndex < PID_TYPE_COUNT; pidIndex++) {
        PidParameter* localPidParameter = getPidParameterByIndex(pidMotion, pidIndex);
        internalSavePidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_KP, localPidParameter->p);
        internalSavePidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_KI, localPidParameter->i);
        internalSavePidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_KD, localPidParameter->d);
        internalSavePidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_MI, localPidParameter->maxIntegral);
    }
    
    MotionEndDetectionParameter* motionEndDetectionParameter = &(pidMotion->globalParameters.motionEndDetectionParameter);
    saveMotionEndDetectionParameters(motionEndDetectionParameter, pidMotion->pidPersistenceEeprom);
}
