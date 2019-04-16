#include "motionParameterPersistence.h"

#include <stdbool.h>
#include <stdlib.h>

#include "motionParameterType.h"
#include "motionParameter.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/eepromAreas.h"
#include "../../common/error/error.h"

// Store speed or acceleration (4 bytes for float on eeprom)
#define MOTION_PARAMETER_DATA_SIZE                     4

// Count values
#define MOTION_PARAMETERS_VALUES_COUNT                  MOTION_PARAMETERS_COUNT * 2


// EEPROM values
static float MOTION_PARAMETERS_DEFAULT_EEPROM_VALUES[MOTION_PARAMETERS_VALUES_COUNT] = {
    DEFAULT_FORWARD_ACCELERATION,                    DEFAULT_FORWARD_SPEED,
    DEFAULT_ROTATION_ACCELERATION,                   DEFAULT_ROTATION_SPEED,
    DEFAULT_ROTATION_ONE_WHEEL_ACCELERATION,         DEFAULT_ROTATION_ONE_WHEEL_SPEED,
    DEFAULT_ROTATION_MAINTAIN_POSITION_ACCELERATION, DEFAULT_ROTATION_MAINTAIN_POSITION_SPEED
};

// CHECK

/**
 * Check if the eeprom is initialized
 * @param _eeprom the eeprom object structure
 * @return 
 */
bool internalMotionParametersCheckIfEepromIsNotNull(Eeprom* _eeprom) {
    if (_eeprom == NULL) {
        writeError(MOTION_PARAMETERS_PERSISTENCE_NO_EEPROM);
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
bool internalMotionParametersCheckIfEepromIsInitialized(Eeprom* _eeprom) {
    bool motionParametersEepromAreaIsInitialized = isEepromAreaInitialized(_eeprom, EEPROM_MOTION_PARAMETERS_AREA_MARKER_INDEX);
    if (!motionParametersEepromAreaIsInitialized) {
        writeError(MOTION_PARAMETERS_PERSISTENCE_EEPROM_NOT_INITIALIZED);
        return false;
    }
    return true;
}

float internalLoadMotionParameterItem(Eeprom* motionParameterEeprom, unsigned long index, unsigned int digitPrecision, bool loadDefaultValues) {
    // Check of eeprom (not null, initialized) are done by caller
    float result;
    if (loadDefaultValues) {
        result = MOTION_PARAMETERS_DEFAULT_EEPROM_VALUES[index];
    }
    else {
        unsigned long dataIndex = EEPROM_MOTION_PARAMETERS_START_INDEX + index * MOTION_PARAMETER_DATA_SIZE;
        result = eepromReadUnsignedFloat(motionParameterEeprom, dataIndex, digitPrecision);
    }
    return result;
}

void internalSaveMotionParameterItem(Eeprom* motionParameterEeprom, unsigned long index, float value, unsigned int digitPrecision) {
    // Check of eeprom (not null, initialized) are done by caller
    unsigned long dataIndex = EEPROM_MOTION_PARAMETERS_START_INDEX + index * MOTION_PARAMETER_DATA_SIZE;
    eepromWriteUnsignedFloat(motionParameterEeprom, dataIndex, value, digitPrecision);
}

void internalLoadMotionParameter(Eeprom* motionParameterEeprom, enum MotionParameterType motionParameterType, bool loadDefaultValues) {
    float a = internalLoadMotionParameterItem(motionParameterEeprom, (int) motionParameterType * 2, MOTION_PARAMETERS_ACCELERATION_DIGIT, loadDefaultValues);
    float speed = internalLoadMotionParameterItem(motionParameterEeprom, (int) motionParameterType * 2 + 1, MOTION_PARAMETERS_SPEED_DIGIT, loadDefaultValues);

    MotionParameter* motionParameter = getMotionParameters(motionParameterType);
    motionParameter->a = a;
    motionParameter->speed = speed;
}

void internalSaveMotionParameter(Eeprom* motionParameterEeprom, enum MotionParameterType motionParameterType) {
    MotionParameter* motionParameter = getMotionParameters(motionParameterType);
    internalSaveMotionParameterItem(motionParameterEeprom, (int) motionParameterType * 2, motionParameter->a, MOTION_PARAMETERS_ACCELERATION_DIGIT);
    internalSaveMotionParameterItem(motionParameterEeprom, (int) motionParameterType * 2 + 1, motionParameter->speed, MOTION_PARAMETERS_SPEED_DIGIT);
}

// Interface Implementation

void loadMotionParameters(Eeprom* motionParameterEeprom, bool loadDefaultValues) {    
    if (!loadDefaultValues) {
        if (!internalMotionParametersCheckIfEepromIsNotNull(motionParameterEeprom)) {
            return;
        }
        if (!internalMotionParametersCheckIfEepromIsInitialized(motionParameterEeprom)) {
            return;
        }
    }
    enum MotionParameterType motionType;
    for (motionType = 0; motionType < MOTION_PARAMETERS_COUNT; motionType++) {
        internalLoadMotionParameter(motionParameterEeprom, motionType, loadDefaultValues);
    }
}

void saveMotionParameters(Eeprom* motionParameterEeprom) {
    if (!internalMotionParametersCheckIfEepromIsNotNull(motionParameterEeprom)) {
        return;
    }

    // Mark the Eeprom Area
    initEepromArea(motionParameterEeprom, EEPROM_MOTION_PARAMETERS_AREA_MARKER_INDEX);

    // initializes all values
    enum MotionParameterType motionType;
    for (motionType = 0; motionType < MOTION_PARAMETERS_COUNT; motionType++) {
        internalSaveMotionParameter(motionParameterEeprom, motionType);
    }
}

