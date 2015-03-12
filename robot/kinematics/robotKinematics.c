#include "robotKinematics.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/eepromAreas.h"
#include "../../common/error/error.h"

// Singleton
static RobotKinematics robotKinematicsInstance;

RobotKinematics* getRobotKinematics(void) {
	return &robotKinematicsInstance;
}


float getLeftWheelLengthForOnePulse(RobotKinematics* robotKinematics) {
	return (robotKinematics->wheelAverageLengthForOnePulse + robotKinematics->wheelDeltaLengthForOnePulse);
}

float getRightWheelLengthForOnePulse(RobotKinematics* robotKinematics) {
	return (robotKinematics->wheelAverageLengthForOnePulse - robotKinematics->wheelDeltaLengthForOnePulse);
}

float getWheelPulseBySecondsAtFullSpeed(RobotKinematics* robotKinematics) {
	return (robotKinematics->wheelRotationBySecondsAtFullSpeed * robotKinematics->pulseByRotation);
}
 
float getWheelsDistanceFromCenter(RobotKinematics* robotKinematics) {
	return robotKinematics->wheelsDistance / 2.0f;
}

void loadRobotKinematicsParameters(RobotKinematics* robotKinematics, Eeprom* eeprom_, bool loadDefaultValues) {
	if (eeprom_ == NULL) {
		writeError(ROBOT_KINEMATICS_NO_EEPROM);
		return;
	}

	if (loadDefaultValues) {
		robotKinematics->wheelAverageLengthForOnePulse = KINEMATICS_WHEEL_AVERAGE_LENGTH_DEFAULT_VALUE;
		robotKinematics->wheelRotationBySecondsAtFullSpeed = KINEMATICS_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED_DEFAULT_VALUE;
		robotKinematics->pulseByRotation = KINEMATICS_WHEEL_PULSE_BY_ROTATION_DEFAULT_VALUE;
		robotKinematics->wheelDeltaLengthForOnePulse = KINEMATICS_WHEEL_DELTA_LENGTH_DEFAULT_VALUE;
		robotKinematics->wheelsDistance = KINEMATICS_WHEELS_DISTANCE_DEFAULT_VALUE;
	}
	else {
        bool eepromKinematicsAreaInitialized = isEepromAreaInitialized(eeprom_, EEPROM_KINETICS_AREA_MARKER_INDEX);
    	if (!eepromKinematicsAreaInitialized) {
    		writeError(ROBOT_KINEMATICS_EEPROM_NOT_INITIALIZED);
    		return;
    	}
		// We store a value * 10^6 (millimeter->nanometer)
		robotKinematics->wheelAverageLengthForOnePulse = (float) eepromReadLong(eeprom_, EEPROM_WHEEL_AVERAGE_LENGTH_FOR_ONE_PULSE_INDEX) / MILLI_TO_NANO_FACTOR;
		robotKinematics->wheelRotationBySecondsAtFullSpeed = (float) eepromReadLong(eeprom_, EEPROM_WHEEL_ROTATION_BY_SECOND_AT_FULL_SPEED_INDEX);
		robotKinematics->pulseByRotation = (float) eepromReadLong(eeprom_, EEPROM_PULSE_BY_ROTATION_INDEX);
		// We store a value * 10^6 (millimeter->nanometer)
		robotKinematics->wheelDeltaLengthForOnePulse = (float) eepromReadLong(eeprom_, EEPROM_WHEEL_DELTA_LENGTH_INDEX) / MILLI_TO_NANO_FACTOR;
		// We store a value * 10^3 (millimeter->micrometer)
		robotKinematics->wheelsDistance = (float) eepromReadLong(eeprom_, EEPROM_WHEELS_DISTANCE_INDEX) / MILLI_TO_MICRO_FACTOR;
	}
}

void saveRobotKinematicsParameters(RobotKinematics* robotKinematics, Eeprom* eeprom_) {
	if (eeprom_ == NULL) {
		writeError(ROBOT_KINEMATICS_NO_EEPROM);
		return;
	}
	initEepromArea(eeprom_, EEPROM_KINETICS_AREA_MARKER_INDEX);
	// We store a value * 10^6 (millimeter->nanometer)
	eepromWriteLong(eeprom_, EEPROM_WHEEL_AVERAGE_LENGTH_FOR_ONE_PULSE_INDEX, (long) (robotKinematics->wheelAverageLengthForOnePulse * MILLI_TO_NANO_FACTOR));
	eepromWriteLong(eeprom_, EEPROM_WHEEL_ROTATION_BY_SECOND_AT_FULL_SPEED_INDEX, (long) (robotKinematics->wheelRotationBySecondsAtFullSpeed));
	eepromWriteLong(eeprom_, EEPROM_PULSE_BY_ROTATION_INDEX, (long) (robotKinematics->pulseByRotation));
	eepromWriteLong(eeprom_, EEPROM_WHEEL_DELTA_LENGTH_INDEX, (long) (robotKinematics->wheelDeltaLengthForOnePulse * MILLI_TO_NANO_FACTOR));
	eepromWriteLong(eeprom_, EEPROM_WHEELS_DISTANCE_INDEX, (long) (robotKinematics->wheelsDistance * MILLI_TO_MICRO_FACTOR));
}
