#include "robotKinematics.h"
#include "robotKinematicsDevice.h"
#include "robotKinematicsDeviceInterface.h"

#include "../../common/cmd/commonCommand.h"
#include "../../common/eeprom/eeprom.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"

#include "../../drivers/driver.h"

static Eeprom* robotKinematicsEeprom;

void deviceRobotKinematicsInit(void) {

}

void deviceRobotKinematicsShutDown(void) {

}

bool isRobotKinematicsDeviceOk(void) {
    return true;
}

void deviceRobotKinematicsHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
	if (commandHeader == COMMAND_KINEMATICS_LOAD_DEFAULT_VALUES) {
		ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_KINEMATICS_LOAD_DEFAULT_VALUES);
		RobotKinematics* robotKinematics = getRobotKinematics();
		loadRobotKinematicsParameters(robotKinematics, robotKinematicsEeprom, true);
		saveRobotKinematicsParameters(robotKinematics, robotKinematicsEeprom);
	}
	else if (commandHeader == COMMAND_GET_WHEELS_AVERAGE_FOR_ONE_PULSE_LENGTH) {
		ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_GET_WHEELS_AVERAGE_FOR_ONE_PULSE_LENGTH);
		RobotKinematics* robotKinematics = getRobotKinematics();
		appendHex6(outputStream, (long) (robotKinematics->wheelAverageLengthForOnePulse * MILLI_TO_NANO_FACTOR));
	}
	else if (commandHeader == COMMAND_SET_WHEELS_AVERAGE_FOR_ONE_PULSE_LENGTH) {
		ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_WHEELS_AVERAGE_FOR_ONE_PULSE_LENGTH);
		RobotKinematics* robotKinematics = getRobotKinematics();
		float value = (float) readHex6(inputStream);
		robotKinematics->wheelAverageLengthForOnePulse = value / MILLI_TO_NANO_FACTOR;
	}
	else if (commandHeader == COMMAND_GET_ROTATION_BY_SECONDS_AT_FULL_SPEED) {
		ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_GET_ROTATION_BY_SECONDS_AT_FULL_SPEED);
		RobotKinematics* robotKinematics = getRobotKinematics();
		appendHex2(outputStream, (unsigned char) robotKinematics->wheelRotationBySecondsAtFullSpeed);
	}
	else if (commandHeader == COMMAND_SET_ROTATION_BY_SECONDS_AT_FULL_SPEED) {
		ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_ROTATION_BY_SECONDS_AT_FULL_SPEED);
		RobotKinematics* robotKinematics = getRobotKinematics();
		float value = (float)readHex2(inputStream);
		robotKinematics->wheelRotationBySecondsAtFullSpeed = value;
	}
	else if (commandHeader == COMMAND_GET_PULSE_BY_ROTATION) {
		ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_GET_PULSE_BY_ROTATION);
		RobotKinematics* robotKinematics = getRobotKinematics();
		appendHex4(outputStream, (unsigned int) robotKinematics->pulseByRotation);
	}
	else if (commandHeader == COMMAND_SET_PULSE_BY_ROTATION) {
		ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_PULSE_BY_ROTATION);
		RobotKinematics* robotKinematics = getRobotKinematics();
		float value = (float)readHex4(inputStream);
		robotKinematics->pulseByRotation = value;
	}
	else if (commandHeader == COMMAND_GET_WHEEL_DELTA_FOR_ONE_PULSE_LENGTH) {
		ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_GET_WHEEL_DELTA_FOR_ONE_PULSE_LENGTH);
		RobotKinematics* robotKinematics = getRobotKinematics();
		appendHex6(outputStream, (long) (robotKinematics->wheelDeltaLengthForOnePulse * MILLI_TO_NANO_FACTOR));
	}
	else if (commandHeader == COMMAND_SET_WHEELS_AVERAGE_FOR_ONE_PULSE_LENGTH) {
		ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_WHEELS_AVERAGE_FOR_ONE_PULSE_LENGTH);
		RobotKinematics* robotKinematics = getRobotKinematics();
		float value = (float)readHex6(inputStream);
		robotKinematics->wheelDeltaLengthForOnePulse = value / MILLI_TO_NANO_FACTOR;
	}
	else if (commandHeader == COMMAND_GET_WHEELS_DISTANCE) {
		ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_GET_WHEELS_DISTANCE);
		RobotKinematics* robotKinematics = getRobotKinematics();
		appendHex6(outputStream, (long) (robotKinematics->wheelsDistance * MILLI_TO_MICRO_FACTOR));
	}
	else if (commandHeader == COMMAND_SET_WHEELS_DISTANCE) {
		ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_WHEELS_DISTANCE);
		RobotKinematics* robotKinematics = getRobotKinematics();
		float value = (float)readHex6(inputStream);
		robotKinematics->wheelsDistance = value / MILLI_TO_MICRO_FACTOR;
	}
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceRobotKinematicsInit,
    .deviceShutDown = &deviceRobotKinematicsShutDown,
    .deviceIsOk = &isRobotKinematicsDeviceOk,
    .deviceHandleRawData = &deviceRobotKinematicsHandleRawData
};

DeviceDescriptor* getRobotKinematicsDeviceDescriptor(Eeprom* eeprom_) {
    robotKinematicsEeprom = eeprom_;
    return &descriptor;
}
