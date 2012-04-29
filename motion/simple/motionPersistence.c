#include "motionPersistence.h"
#include "motion.h"

#include "../../common/eeprom/eeprom.h"

// Store speed and acceleration
#define MOTION_PARAMETERS_VALUES_COUNT 			MOTION_PARAMETERS_COUNT * 2

// EEPROM values
signed int DEFAULT_EEPROM_VALUES[MOTION_PARAMETERS_VALUES_COUNT] = {
    DEFAULT_FORWARD_ACCELERATION, DEFAULT_FORWARD_SPEED,
    DEFAULT_ROTATION_ACCELERATION, DEFAULT_ROTATION_SPEED,
    DEFAULT_ROTATION_ONE_WHEEL_ACCELERATION, DEFAULT_ROTATION_ONE_WHEEL_SPEED,
    DEFAULT_ROTATION_MAINTAIN_POSITION_ACCELERATION, DEFAULT_ROTATION_MAINTAIN_POSITION_SPEED
};

#define EEPROM_MOTION_TYPE_BLOCK_SIZE							 MOTION_PARAMETERS_COUNT

signed int internalLoadMotionParameterItem(unsigned int dataIndex) {
    signed int result = my_eeprom_read_int(dataIndex);
    if (result == 0xFFFF) {
        result = DEFAULT_EEPROM_VALUES[dataIndex - EEPROM_MOTION_START_INDEX];
    }
    return result;
}

void internalLoadMotionParameter(unsigned char motionType) {
    unsigned motionBlockIndexShift = motionType * EEPROM_MOTION_TYPE_BLOCK_SIZE;
    unsigned int a = internalLoadMotionParameterItem(EEPROM_MOTION_START_INDEX + motionBlockIndexShift);
    unsigned int speed = internalLoadMotionParameterItem(EEPROM_MOTION_START_INDEX + motionBlockIndexShift + 1);

    MotionParameter* motionParameter = getDefaultMotionParameters(motionType);
    motionParameter->a = a;
    motionParameter->speed = speed;
}

void internalSaveMotionParameter(unsigned char motionType) {
    MotionParameter* motionParameter = getDefaultMotionParameters(motionType);
    unsigned motionBlockIndexShift = motionType * EEPROM_MOTION_TYPE_BLOCK_SIZE;
    my_eeprom_write_int(EEPROM_MOTION_START_INDEX + motionBlockIndexShift, motionParameter->a);
    my_eeprom_write_int(EEPROM_MOTION_START_INDEX + motionBlockIndexShift + 1, motionParameter->speed);
}

// Interface Implementation

void loadMotionParameters() {
    int i;
    for (i = 0; i < MOTION_PARAMETERS_COUNT; i++) {
        internalLoadMotionParameter(i);
    }
}

void saveMotionParameters() {
    int i;
    for (i = 0; i < MOTION_PARAMETERS_COUNT; i++) {
        internalSaveMotionParameter(i);
    }
}

