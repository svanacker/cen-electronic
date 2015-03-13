#include "motionPersistence.h"

#include <stdbool.h>
#include <stdlib.h>

#include "motionParameterType.h"
#include "motionParameter.h"

#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/eepromAreas.h"
#include "../../common/error/error.h"

// Store speed and acceleration
#define MOTION_PARAMETER_BLOCK_SIZE                2

// Count values
#define MOTION_PARAMETERS_VALUES_COUNT             MOTION_PARAMETERS_COUNT * 2

// EEPROM values
static unsigned char DEFAULT_EEPROM_VALUES[MOTION_PARAMETERS_VALUES_COUNT] = {
    DEFAULT_FORWARD_ACCELERATION, DEFAULT_FORWARD_SPEED,
    DEFAULT_ROTATION_ACCELERATION, DEFAULT_ROTATION_SPEED,
    DEFAULT_ROTATION_ONE_WHEEL_ACCELERATION, DEFAULT_ROTATION_ONE_WHEEL_SPEED,
    DEFAULT_ROTATION_MAINTAIN_POSITION_ACCELERATION, DEFAULT_ROTATION_MAINTAIN_POSITION_SPEED
};

static Eeprom* motionPersistenceEeprom;

unsigned char internalLoadMotionParameterItem(Eeprom* eeprom, unsigned long dataIndex, bool loadDefaultValues) {
    if (motionPersistenceEeprom == NULL) {
        writeError(MOTION_PERSISTENCE_NO_EEPROM);
        return 0;
    }
	bool motionEepromAreaIsInitialized = isEepromAreaInitialized(eeprom, EEPROM_MOTION_AREA_MARKER_INDEX);
    unsigned char result;
    if (loadDefaultValues) {
        result = DEFAULT_EEPROM_VALUES[dataIndex - EEPROM_MOTION_START_INDEX];
    }
    else {
    	if (!motionEepromAreaIsInitialized) {
    		writeError(MOTION_PERSISTENCE_EEPROM_NOT_INITIALIZED);
    		return 0;
    	}
        result = motionPersistenceEeprom->eepromReadChar(motionPersistenceEeprom, dataIndex);
    }
    return result;
}

void internalLoadMotionParameter(Eeprom* eeprom, enum MotionParameterType motionParameterType, bool loadDefaultValues) {
    if (motionPersistenceEeprom == NULL) {
        writeError(MOTION_PERSISTENCE_NO_EEPROM);
        return;
    }
    unsigned long motionBlockIndexShift = motionParameterType * MOTION_PARAMETER_BLOCK_SIZE;
    float a = (float) internalLoadMotionParameterItem(eeprom, EEPROM_MOTION_START_INDEX + motionBlockIndexShift, loadDefaultValues);
    float speed = (float) internalLoadMotionParameterItem(eeprom, EEPROM_MOTION_START_INDEX + motionBlockIndexShift + 1, loadDefaultValues);

    MotionParameter* motionParameter = getDefaultMotionParameters(motionParameterType);
    motionParameter->a = a;
    motionParameter->speed = speed;
}

void internalSaveMotionParameter(Eeprom* eeprom, enum MotionParameterType motionType) {
    MotionParameter* motionParameter = getDefaultMotionParameters(motionType);
    unsigned motionBlockIndexShift = motionType * MOTION_PARAMETER_BLOCK_SIZE;
    motionPersistenceEeprom->eepromWriteChar(motionPersistenceEeprom, EEPROM_MOTION_START_INDEX + motionBlockIndexShift, (int) motionParameter->a);
    motionPersistenceEeprom->eepromWriteChar(motionPersistenceEeprom, EEPROM_MOTION_START_INDEX + motionBlockIndexShift + 1, (int) motionParameter->speed);
}

// Interface Implementation

void loadMotionParameters(Eeprom* eeprom, bool loadDefaultValues) {    
    motionPersistenceEeprom = eeprom;
    enum MotionParameterType motionType;
    for (motionType = 0; motionType < MOTION_PARAMETERS_COUNT; motionType++) {
        internalLoadMotionParameter(eeprom, motionType, loadDefaultValues);
    }
}

void saveMotionParameters(Eeprom* motionEeprom) {
	initEepromArea(motionEeprom, EEPROM_MOTION_AREA_MARKER_INDEX);
    enum MotionParameterType motionType;
    for (motionType = 0; motionType < MOTION_PARAMETERS_COUNT; motionType++) {
        internalSaveMotionParameter(motionEeprom, motionType);
    }
}

