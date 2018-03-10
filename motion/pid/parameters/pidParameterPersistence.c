#include "pidParameterPersistence.h"

#include <stdlib.h>

#include "../pid.h"
#include "../parameters/pidParameter.h"

#include "../../../common/commons.h"
#include "../../../common/eeprom/eeprom.h"
#include "../../../common/eeprom/eepromAreas.h"
#include "../../../common/error/error.h"

// DEFAULT VALUES : As the PID value is stored into the eeprom, this will be erased by 
// Programming. It's very dangerous if we forget to send default values
#define PID_STORED_COUNT        8

static float PID_PARAMETERS_EEPROM_DEFAULT_VALUES[EEPROM_PID_PARAMETERS_VALUE_COUNT * PID_STORED_COUNT] = {
    // NORMAL VALUES
    // Go (P I D MI)
    0.5f, 0.0f, 0.3f, 0.0f,
    0x5f, 0.0f, 0.3f, 0.0f,
    // Rotation (P I D MI)
    0.5f, 0.0f, 0.3f, 0.0f,
    0.5f, 0.0f, 0.3f, 0.0f,
    // Maintain Position
    1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    // Adjust to the border : it needs small Alpha PID to be able to adjust to the border
    0.2f, 0.0f, 0.3f, 0.0f,
    0.05f, 0.0f, 0.3f, 0.0f,
};

// Values not stored into the EEPROM
#define ROLLING_TEST_P                0.1f
#define ROLLING_TEST_I                0.0f
#define ROLLING_TEST_D                0.1f
#define ROLLING_TEST_MAX_INTEGRAL     0.1f

#define END_APPROACH_P                1.0f
#define END_APPROACH_I                0.0f
#define END_APPROACH_D                1.0f
#define END_APPROACH_MAX_INTEGRAL     0.0f

// Not used
#define DEFAULT_MAX_INTEGRAL 0

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
 * @param pidIndex the index of PID (between 0 and PID_COUNT)
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
        unsigned long realDataEepromIndex = EEPROM_PID_PARAMETERS_START_INDEX + realIndex * EEPROM_PID_PARAMETERS_VALUE_LENGTH;
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
    int pidIndex;
    for (pidIndex = 0; pidIndex < PID_STORED_COUNT; pidIndex++) {
        PidParameter* localPidParameter = getPidParameter(pidMotion, pidIndex, 0);
        localPidParameter->p = internalLoadPidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_KP, loadDefaultValues);
        localPidParameter->i = internalLoadPidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_KI, loadDefaultValues);
        localPidParameter->d = internalLoadPidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_KD, loadDefaultValues);
        localPidParameter->maxIntegral = internalLoadPidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_MI, loadDefaultValues);
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
    for (instructionType = 0; instructionType < INSTRUCTION_TYPE_COUNT; instructionType++) {
        pidIndex = getIndexOfPid(instructionType, PID_TYPE_FINAL_APPROACH_INDEX);
        PidParameter* endApproachPidParameter = getPidParameter(pidMotion, pidIndex, 0);
        endApproachPidParameter->p = END_APPROACH_P;
        endApproachPidParameter->i = END_APPROACH_I;
        endApproachPidParameter->d = END_APPROACH_D;
        endApproachPidParameter->maxIntegral = END_APPROACH_MAX_INTEGRAL;
        endApproachPidParameter->enabled = true;
    }
    
    // Load Motion End Detection Parameter
    MotionEndDetectionParameter* motionEndDetectionParameter = &(pidMotion->globalParameters.motionEndDetectionParameter);
    if (loadDefaultValues) {
        motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold = ABS_DELTA_POSITION_INTEGRAL_FACTOR_THRESHOLD_DEFAULT_VALUE;
        motionEndDetectionParameter->maxUIntegralFactorThreshold = MAX_U_INTEGRAL_FACTOR_THRESHOLD_DEFAULT_VALUE;
        motionEndDetectionParameter->maxUIntegralConstantThreshold = MAX_U_INTEGRAL_CONSTANT_THRESHOLD_DEFAULT_VALUE;
        motionEndDetectionParameter->noAnalysisAtStartupTimeInSecond = BLOCKING_OR_REACH_SKIP_DETECTION_DELAY_DEFAULT_VALUE;
        motionEndDetectionParameter->timeRangeAnalysisInSecond = BLOCKING_OR_REACH_DETECTION_DELAY_DEFAULT_VALUE;
    }
    else {
        Eeprom* _eeprom = pidMotion->pidPersistenceEeprom;
        motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold = eepromReadUnsignedFloat(_eeprom, EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX, MOTION_END_DETECTION_PARAMETER_DIGIT);
        motionEndDetectionParameter->maxUIntegralFactorThreshold = eepromReadUnsignedFloat(_eeprom, EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX + 4, MOTION_END_DETECTION_PARAMETER_DIGIT);
        motionEndDetectionParameter->maxUIntegralConstantThreshold = eepromReadUnsignedFloat(_eeprom, EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX + 8, MOTION_END_DETECTION_PARAMETER_DIGIT);
        motionEndDetectionParameter->noAnalysisAtStartupTimeInSecond = eepromReadUnsignedFloat(_eeprom, EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX + 12, MOTION_END_DETECTION_PARAMETER_DIGIT);
        motionEndDetectionParameter->timeRangeAnalysisInSecond = eepromReadUnsignedFloat(_eeprom, EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX + 16, MOTION_END_DETECTION_PARAMETER_DIGIT);
    }
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
    for (pidIndex = 0; pidIndex < PID_STORED_COUNT; pidIndex++) {
        PidParameter* localPidParameter = getPidParameter(pidMotion, pidIndex, 0);
        internalSavePidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_KP, localPidParameter->p);
        internalSavePidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_KI, localPidParameter->i);
        internalSavePidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_KD, localPidParameter->d);
        internalSavePidParameter(pidMotion, pidIndex, PID_PARAMETERS_EEPROM_INDEX_MI, localPidParameter->maxIntegral);
    }
    
    // Store Motion End Detection Parameter
    Eeprom* _eeprom = pidMotion->pidPersistenceEeprom;
    MotionEndDetectionParameter* motionEndDetectionParameter = &(pidMotion->globalParameters.motionEndDetectionParameter);
    eepromWriteUnsignedFloat(_eeprom, EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX, motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold, MOTION_END_DETECTION_PARAMETER_DIGIT);
    eepromWriteUnsignedFloat(_eeprom, EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX + 4, motionEndDetectionParameter->maxUIntegralFactorThreshold, MOTION_END_DETECTION_PARAMETER_DIGIT);
    eepromWriteUnsignedFloat(_eeprom, EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX + 8, motionEndDetectionParameter->maxUIntegralConstantThreshold, MOTION_END_DETECTION_PARAMETER_DIGIT);
    eepromWriteUnsignedFloat(_eeprom, EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX + 12, motionEndDetectionParameter->noAnalysisAtStartupTimeInSecond, MOTION_END_DETECTION_PARAMETER_DIGIT);
    eepromWriteUnsignedFloat(_eeprom, EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX + 16, motionEndDetectionParameter->timeRangeAnalysisInSecond, MOTION_END_DETECTION_PARAMETER_DIGIT);
}
