#include "robotKinematics.h"
#include "robotKinematicsPersistence.h"
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

#include "../../robot/kinematics/robotKinematics.h"
#include "../../robot/kinematics/robotKinematicsDebug.h"

static Eeprom* robotKinematicsEeprom;

void deviceRobotKinematicsInit(void) {
    RobotKinematics* robotKinematics = getRobotKinematics();
    // Load from the eeprom but do not overwrite by reading default values
	loadRobotKinematicsParameters(robotKinematics, robotKinematicsEeprom, false);
}

void deviceRobotKinematicsShutDown(void) {

}

bool isRobotKinematicsDeviceOk(void) {
    return true;
}

void deviceRobotKinematicsHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_KINEMATICS_LOAD_DEFAULT_VALUES) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_KINEMATICS_LOAD_DEFAULT_VALUES);
        RobotKinematics* robotKinematics = getRobotKinematics();
        loadRobotKinematicsParameters(robotKinematics, robotKinematicsEeprom, true);
    }
    else if (commandHeader == COMMAND_KINEMATICS_SAVE) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_KINEMATICS_SAVE);
        RobotKinematics* robotKinematics = getRobotKinematics();
        saveRobotKinematicsParameters(robotKinematics, robotKinematicsEeprom);
    }
    else if (commandHeader == COMMAND_KINEMATICS_LIST_DEBUG) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_KINEMATICS_LIST_DEBUG);
        RobotKinematics* robotKinematics = getRobotKinematics();
        printRobotKinematicsTable(getAlwaysOutputStreamLogger(), robotKinematics);
    }
    // READ ALL
    // wheelAverageLengthForOnePulse
    else if (commandHeader == COMMAND_KINEMATICS_READ_ALL) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_KINEMATICS_READ_ALL);
        RobotKinematics* robotKinematics = getRobotKinematics();
        // CODER PART
        appendHex6(outputStream, (long) (robotKinematics->coderWheelAverageDiameterMM * MILLI_TO_MICRO_FACTOR));
        appendSeparator(outputStream);
        appendHex6(outputStream, (long)(robotKinematics->coderWheelAverageDeltaDiameterMM * MILLI_TO_MICRO_FACTOR));
        appendSeparator(outputStream);
        appendHex6(outputStream, (long)(robotKinematics->coderWheelDistanceBetweenWheelsMM * MILLI_TO_MICRO_FACTOR));
        appendSeparator(outputStream);
        appendHex6(outputStream, (long)(robotKinematics->coderWheelPulseByRotation));
        appendSeparator(outputStream);
        // MOTOR PART
        appendHex6(outputStream, (long)(robotKinematics->motorWheelAverageDiameterMM * MILLI_TO_MICRO_FACTOR));
        appendSeparator(outputStream);
        appendHex6(outputStream, (long)(robotKinematics->motorWheelDistanceBetweenWheelsMM * MILLI_TO_MICRO_FACTOR));
        appendSeparator(outputStream);
        appendHex6(outputStream, (long)(robotKinematics->motorWheelRotationBySecondAtFullSpeed));
    }
    // CODER PART
    else if (commandHeader == COMMAND_SET_CODER_WHEEL_AVERAGE_DIAMETER_MM) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_CODER_WHEEL_AVERAGE_DIAMETER_MM);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = (float) readHex6(inputStream);
        robotKinematics->coderWheelAverageDiameterMM = value / MILLI_TO_MICRO_FACTOR;
    }
    else if (commandHeader == COMMAND_SET_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_MM) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_MM);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = (float)readHex6(inputStream);
        robotKinematics->coderWheelAverageDeltaDiameterMM = value / MILLI_TO_MICRO_FACTOR;
    }
    else if (commandHeader == COMMAND_SET_CODER_DISTANCE_BETWEEN_WHEELS_MM) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_CODER_DISTANCE_BETWEEN_WHEELS_MM);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = (float)readHex6(inputStream);
        robotKinematics->coderWheelDistanceBetweenWheelsMM =  value / MILLI_TO_MICRO_FACTOR;
    }
    else if (commandHeader == COMMAND_SET_CODER_WHEEL_PULSE_BY_ROTATION) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_CODER_WHEEL_PULSE_BY_ROTATION);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = (float)readHex6(inputStream);
        robotKinematics->coderWheelPulseByRotation = value;
    }
    // MOTOR PART
    else if (commandHeader == COMMAND_SET_MOTOR_WHEEL_AVERAGE_DIAMETER_MM) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_MOTOR_WHEEL_AVERAGE_DIAMETER_MM);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = (float)readHex6(inputStream);
        robotKinematics->motorWheelAverageDiameterMM = value / MILLI_TO_MICRO_FACTOR;
    }
    else if (commandHeader == COMMAND_SET_MOTOR_DISTANCE_BETWEEN_WHEELS_MM) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_MOTOR_DISTANCE_BETWEEN_WHEELS_MM);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = (float)readHex6(inputStream);
        robotKinematics->motorWheelDistanceBetweenWheelsMM = value / MILLI_TO_MICRO_FACTOR;
    }
    else if (commandHeader == COMMAND_SET_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = (float)readHex6(inputStream);
        robotKinematics->motorWheelRotationBySecondAtFullSpeed = value;
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
