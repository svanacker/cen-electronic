#include "motionParameterPersistence.h"

#include <stdbool.h>
#include <stdlib.h>

#include "motionParameterType.h"
#include "motionParameter.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/eepromAreas.h"
#include "../../common/error/error.h"

// Store speed (4 bytes for float) and acceleration (4 bytes for float)
#define MOTION_PARAMETER_BLOCK_SIZE                     8

// Count values
#define MOTION_PARAMETERS_VALUES_COUNT                  MOTION_PARAMETERS_COUNT * 2

#define MOTION_PARAMETERS_SPEED_EEPROM_DIGIT            0
#define MOTION_PARAMETERS_ACCELERATION_EEPROM_DIGIT     2

// EEPROM values
static unsigned float DEFAULT_EEPROM_VALUES[MOTION_PARAMETERS_VALUES_COUNT] = {
    DEFAULT_FORWARD_ACCELERATION,                    DEFAULT_FORWARD_SPEED,
    DEFAULT_ROTATION_ACCELERATION,                   DEFAULT_ROTATION_SPEED,
    DEFAULT_ROTATION_ONE_WHEEL_ACCELERATION,         DEFAULT_ROTATION_ONE_WHEEL_SPEED,
    DEFAULT_ROTATION_MAINTAIN_POSITION_ACCELERATION, DEFAULT_ROTATION_MAINTAIN_POSITION_SPEED
};

float internalLoadMotionParameterItem(Eeprom* motionParameterEeprom, unsigned long dataIndex, bool loadDefaultValues) {
    if (motionParameterEeprom == NULL) {
        writeError(MOTION_PARAMETERS_PERSISTENCE_NO_EEPROM);
        return 0;
    }
    bool motionEepromAreaIsInitialized = isEepromAreaInitialized(motionParameterEeprom, EEPROM_MOTION_PARAMETERS_AREA_MARKER_INDEX);
    unsigned char result;
    if (loadDefaultValues) {
        result = DEFAULT_EEPROM_VALUES[dataIndex - EEPROM_MOTION_PARAMETERS_START_INDEX];
    }
    else {
        if (!motionEepromAreaIsInitialized) {
            writeError(MOTION_PARAMETERS_PERSISTENCE_EEPROM_NOT_INITIALIZED);
            return 0;
        }
        result = eepromReadUnsignedFloat(motionParameterEeprom, dataIndex, MOTION_PARAMETERS_ACCELERATION_EEPROM_DIGIT);
    }
    return result;
}

void internalLoadMotionParameter(Eeprom* motionParameterEeprom, enum MotionParameterType motionParameterType, bool loadDefaultValues) {
    if (motionParameterEeprom == NULL) {
        writeError(MOTION_PARAMETERS_PERSISTENCE_NO_EEPROM);
        return;
    }
    unsigned long motionBlockIndexShift = motionParameterType * MOTION_PARAMETER_BLOCK_SIZE;
    float a = (float) internalLoadMotionParameterItem(motionParameterEeprom, EEPROM_MOTION_PARAMETERS_START_INDEX + motionBlockIndexShift, loadDefaultValues);
    float speed = (float) internalLoadMotionParameterItem(motionParameterEeprom, EEPROM_MOTION_PARAMETERS_START_INDEX + motionBlockIndexShift + 4, loadDefaultValues);

    MotionParameter* motionParameter = getMotionParameters(motionParameterType);
    motionParameter->a = a;
    motionParameter->speed = speed;
}

void internalSaveMotionParameter(Eeprom* motionParameterEeprom, enum MotionParameterType motionType) {
    MotionParameter* motionParameter = getMotionParameters(motionType);
    unsigned motionBlockIndexShift = motionType * MOTION_PARAMETER_BLOCK_SIZE;
    eepromWriteUnsignedFloat(motionParameterEeprom, EEPROM_MOTION_PARAMETERS_START_INDEX + motionBlockIndexShift, motionParameter->a, 0);
    eepromWriteUnsignedFloat(motionParameterEeprom, EEPROM_MOTION_PARAMETERS_START_INDEX + motionBlockIndexShift + 4, motionParameter->speed, 0);
}

// Interface Implementation

void loadMotionParameters(Eeprom* motionParameterEeprom, bool loadDefaultValues) {    
    enum MotionParameterType motionType;
    for (motionType = 0; motionType < MOTION_PARAMETERS_COUNT; motionType++) {
        internalLoadMotionParameter(motionParameterEeprom, motionType, loadDefaultValues);
    }
}

void saveMotionParameters(Eeprom* motionParameterEeprom) {
    initEepromArea(motionParameterEeprom, EEPROM_MOTION_PARAMETERS_AREA_MARKER_INDEX);
    enum MotionParameterType motionType;
    for (motionType = 0; motionType < MOTION_PARAMETERS_COUNT; motionType++) {
        internalSaveMotionParameter(motionParameterEeprom, motionType);
    }
}

