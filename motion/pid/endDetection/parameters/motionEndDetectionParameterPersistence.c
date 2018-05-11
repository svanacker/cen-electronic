#include "motionEndDetectionParameterPersistence.h"
#include "motionEndDetectionParameter.h"

#include "../../../../common/error/error.h"
#include "../../../../common/eeprom/eepromAreas.h"

#include <stdbool.h>
#include <stdlib.h>

#define MOTION_END_DETECTION_PARAMETER_DATA_SIZE                               4
#define MOTION_END_DETECTION_PARAMETERS_VALUES_COUNT                           10
#define MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION                        2

// Relative Index in the Eeprom
// -> DETAIL PHASE
#define MOTION_END_DETECTION_ACCELERATION_TOO_HIGH_THRESHOLD_INDEX     0
#define MOTION_END_DETECTION_SPEED_TOO_LOW_THRESHOLD_INDEX             1
#define MOTION_END_DETECTION_U_TOO_HIGH_THRESHOLD_FACTOR_INDEX         2
#define MOTION_END_DETECTION_SPEED_MIN_THRESHOLD_INDEX                 3
#define MOTION_END_DETECTION_U_MIN_THRESHOLD_INDEX                     4
// -> AGGREGATION PHASE
#define MOTION_END_DETECTION_ABS_DELTA_POSITION_INTEGRAL_FACTOR_THRESHOLD_INDEX 5
#define MOTION_END_DETECTION_MAX_U_INTEGRAL_FACTOR_THRESHOLD_INDEX              6
#define MOTION_END_DETECTION_MAX_U_INTEGRAL_CONSTANT_THRESHOLD_INDEX            7
#define MOTION_END_DETECTION_NO_ANALYSIS_AT_STARTUP_TIME_IN_SECOND_INDEX        8
#define MOTION_END_DETECTION_TIME_RANGE_ANALYSIS_INDEX                          9

// EEPROM values
static float MOTION_END_DETECTION_PARAMETERS_DEFAULT_EEPROM_VALUES[MOTION_END_DETECTION_PARAMETERS_VALUES_COUNT] = {
    ACCELERATION_TOO_HIGH_THRESHOLD_FACTOR_DEFAULT_VALUE,
    SPEED_TOO_LOW_THRESHOLD_FACTOR_DEFAULT_VALUE,
    U_TOO_HIGH_THRESHOLD_FACTOR_DEFAULT_VALUE,
    SPEED_MIN_THRESHOLD_DEFAULT_VALUE,
    U_MIN_THRESHOLD_DEFAULT_VALUE,
    // AGGREGATION PHASE
    ABS_DELTA_POSITION_INTEGRAL_FACTOR_THRESHOLD_DEFAULT_VALUE,
    MAX_U_INTEGRAL_FACTOR_THRESHOLD_DEFAULT_VALUE,
    MAX_U_INTEGRAL_CONSTANT_THRESHOLD_DEFAULT_VALUE,
    BLOCKING_OR_REACH_DETECTION_DELAY_DEFAULT_VALUE,
    BLOCKING_OR_REACH_SKIP_DETECTION_DELAY_DEFAULT_VALUE};

float internalLoadMotionEndDetectionParameterItem(Eeprom* motionParameterEeprom, unsigned long index, unsigned int digitPrecision, bool loadDefaultValues) {
    if (motionParameterEeprom == NULL) {
        // We use the same "MARKER AREA" than for MotionParameterPersistence
        writeError(MOTION_PARAMETERS_PERSISTENCE_NO_EEPROM);
        return 0;
    }
    bool motionEepromAreaIsInitialized = isEepromAreaInitialized(motionParameterEeprom, EEPROM_MOTION_PARAMETERS_AREA_MARKER_INDEX);
    float result;
    if (loadDefaultValues) {
        result = MOTION_END_DETECTION_PARAMETERS_DEFAULT_EEPROM_VALUES[index];
    }
    else {
        if (!motionEepromAreaIsInitialized) {
            writeError(MOTION_PARAMETERS_PERSISTENCE_EEPROM_NOT_INITIALIZED);
            return 0;
        }
        unsigned long dataIndex = EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX + index * MOTION_END_DETECTION_PARAMETER_DATA_SIZE;
        result = eepromReadUnsignedFloat(motionParameterEeprom, dataIndex, digitPrecision);
    }
    return result;
}

void internalSaveMotionEndDetectionParameterItem(Eeprom* motionEndDetectionParametersEeprom, unsigned long index, float value, unsigned int digitPrecision) {
    if (motionEndDetectionParametersEeprom == NULL) {
        writeError(MOTION_PARAMETERS_PERSISTENCE_NO_EEPROM);
        return;
    }
    initEepromArea(motionEndDetectionParametersEeprom, EEPROM_MOTION_PARAMETERS_AREA_MARKER_INDEX);

    unsigned long dataIndex = EEPROM_PID_PARAMETERS_END_DETECTION_START_INDEX + index * MOTION_END_DETECTION_PARAMETER_DATA_SIZE;
    eepromWriteUnsignedFloat(motionEndDetectionParametersEeprom, dataIndex, value, digitPrecision);
}

void loadMotionEndDetectionParameters(MotionEndDetectionParameter* motionEndDetectionParameter, Eeprom* motionEndDetectionParametersEeprom, bool loadDefaultValues) {
    // DETAIL VALUES
    motionEndDetectionParameter->accelerationTooHighTresholdFactor = internalLoadMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom, MOTION_END_DETECTION_ACCELERATION_TOO_HIGH_THRESHOLD_INDEX, MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION, loadDefaultValues);
    motionEndDetectionParameter->speedTooLowThresholdFactor = internalLoadMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom, MOTION_END_DETECTION_SPEED_TOO_LOW_THRESHOLD_INDEX, MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION, loadDefaultValues);
    motionEndDetectionParameter->uTooHighTresholdFactor = internalLoadMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom, MOTION_END_DETECTION_U_TOO_HIGH_THRESHOLD_FACTOR_INDEX, MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION, loadDefaultValues);
    motionEndDetectionParameter->speedMinThreshold = internalLoadMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom, MOTION_END_DETECTION_SPEED_MIN_THRESHOLD_INDEX, MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION, loadDefaultValues);
    motionEndDetectionParameter->uMinThresholdValue = internalLoadMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom, MOTION_END_DETECTION_U_MIN_THRESHOLD_INDEX, MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION, loadDefaultValues);

    // AGGREGATION VALUES
    motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold = internalLoadMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom, MOTION_END_DETECTION_ABS_DELTA_POSITION_INTEGRAL_FACTOR_THRESHOLD_INDEX, MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION, loadDefaultValues);
    motionEndDetectionParameter->maxUIntegralFactorThreshold = internalLoadMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom, MOTION_END_DETECTION_MAX_U_INTEGRAL_FACTOR_THRESHOLD_INDEX, MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION, loadDefaultValues);
    motionEndDetectionParameter->maxUIntegralConstantThreshold = internalLoadMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom, MOTION_END_DETECTION_MAX_U_INTEGRAL_CONSTANT_THRESHOLD_INDEX, MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION, loadDefaultValues);
    motionEndDetectionParameter->noAnalysisAtStartupTimeInSecond = internalLoadMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom, MOTION_END_DETECTION_NO_ANALYSIS_AT_STARTUP_TIME_IN_SECOND_INDEX, MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION, loadDefaultValues);
    motionEndDetectionParameter->timeRangeAnalysisInSecond = internalLoadMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom, MOTION_END_DETECTION_TIME_RANGE_ANALYSIS_INDEX, MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION, loadDefaultValues);
}

void saveMotionEndDetectionParameters(MotionEndDetectionParameter* motionEndDetectionParameter,
                                      Eeprom* motionEndDetectionParametersEeprom) {
    // DETAIL PHASE
    internalSaveMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom,
                                    MOTION_END_DETECTION_ACCELERATION_TOO_HIGH_THRESHOLD_INDEX,
                                    motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold,
                                    MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION);
    
    internalSaveMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom,
                                    MOTION_END_DETECTION_SPEED_TOO_LOW_THRESHOLD_INDEX,
                                    motionEndDetectionParameter->speedTooLowThresholdFactor,
                                    MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION);
    
    internalSaveMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom,
                                    MOTION_END_DETECTION_U_TOO_HIGH_THRESHOLD_FACTOR_INDEX,
                                    motionEndDetectionParameter->uTooHighTresholdFactor,
                                    MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION);

    internalSaveMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom,
                                    MOTION_END_DETECTION_SPEED_MIN_THRESHOLD_INDEX,
                                    motionEndDetectionParameter->speedMinThreshold,
                                    MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION);
    
    internalSaveMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom,
                                    MOTION_END_DETECTION_U_MIN_THRESHOLD_INDEX,
                                    motionEndDetectionParameter->uMinThresholdValue,
                                    MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION);
    
    // AGGREGATION PHASE
    internalSaveMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom,
                                    MOTION_END_DETECTION_ABS_DELTA_POSITION_INTEGRAL_FACTOR_THRESHOLD_INDEX,
                                    motionEndDetectionParameter->absDeltaPositionIntegralFactorThreshold,
                                    MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION);
    
    internalSaveMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom,
                                    MOTION_END_DETECTION_MAX_U_INTEGRAL_FACTOR_THRESHOLD_INDEX,
                                    motionEndDetectionParameter->maxUIntegralFactorThreshold,
                                    MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION);

    internalSaveMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom,
                                    MOTION_END_DETECTION_MAX_U_INTEGRAL_CONSTANT_THRESHOLD_INDEX,
                                    motionEndDetectionParameter->maxUIntegralConstantThreshold,
                                    MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION);
    
    internalSaveMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom,
                                    MOTION_END_DETECTION_NO_ANALYSIS_AT_STARTUP_TIME_IN_SECOND_INDEX,
                                    motionEndDetectionParameter->noAnalysisAtStartupTimeInSecond,
                                    MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION);
    
    internalSaveMotionEndDetectionParameterItem(motionEndDetectionParametersEeprom,
                                    MOTION_END_DETECTION_TIME_RANGE_ANALYSIS_INDEX,
                                    motionEndDetectionParameter->timeRangeAnalysisInSecond,
                                    MOTION_END_DETECTION_PARAMETERS_DIGIT_PRECISION);    
}