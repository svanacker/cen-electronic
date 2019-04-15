#include "robotKinematics.h"
#include "robotKinematicsPersistence.h"
#include "robotKinematicsDevice.h"
#include "robotKinematicsDeviceInterface.h"

#include "../../common/cmd/commonCommand.h"
#include "../../common/eeprom/eeprom.h"
#include "../../common/eeprom/eepromType.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"

#include "../../drivers/driver.h"

#include "../../robot/config/robotConfig.h"

#include "../../robot/kinematics/robotKinematics.h"
#include "../../robot/kinematics/robotKinematicsDebug.h"

static Eeprom* robotKinematicsEeprom;

void deviceRobotKinematicsInit(void) {
    RobotKinematics* robotKinematics = getRobotKinematics();
    // Load from the eeprom but do not overwrite by reading default values unless this is a memory Eeprom
	loadRobotKinematicsParameters(robotKinematics, robotKinematicsEeprom, robotKinematicsEeprom->eepromType == EEPROM_TYPE_MEMORY);
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
        printRobotKinematicsTable(getInfoOutputStreamLogger(), robotKinematics);
    }
    // READ ALL
    // TODO : Split between CODER PART / MOTOR PART / ROBOT PART
    else if (commandHeader == COMMAND_KINEMATICS_READ_ALL) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_KINEMATICS_READ_ALL);
        RobotKinematics* robotKinematics = getRobotKinematics();
        // CODER PART
        appendHexFloat6(outputStream, robotKinematics->coderWheelAverageDiameterMM, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat6(outputStream, robotKinematics->coderWheelAverageDeltaDiameterMM, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat6(outputStream, robotKinematics->coderWheelDistanceBetweenWheelsMM, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat6(outputStream, robotKinematics->coderWheelPulseByRotation, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        appendSeparator(outputStream);
        // MOTOR PART
        appendHexFloat6(outputStream, robotKinematics->motorWheelAverageDiameterMM, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat6(outputStream, robotKinematics->motorWheelDistanceBetweenWheelsMM, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat6(outputStream, robotKinematics->motorWheelRotationBySecondAtFullSpeed, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat6(outputStream, robotKinematics->motorMaxTorqueMilliNewton, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat6(outputStream, robotKinematics->motorReductorRatio, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        // ROBOT PART
        appendSeparator(outputStream);
        appendHexFloat6(outputStream, robotKinematics->robotWeightGrams, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
    }
    // CODER PART
    else if (commandHeader == COMMAND_SET_CODER_WHEEL_AVERAGE_DIAMETER_MM) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_CODER_WHEEL_AVERAGE_DIAMETER_MM);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = readHexFloat6(inputStream, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->coderWheelAverageDiameterMM = value;
    }
    else if (commandHeader == COMMAND_SET_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_MM) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_CODER_WHEEL_AVERAGE_DELTA_DIAMETER_MM);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = readHexFloat6(inputStream, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->coderWheelAverageDeltaDiameterMM = value;
    }
    else if (commandHeader == COMMAND_SET_CODER_DISTANCE_BETWEEN_WHEELS_MM) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_CODER_DISTANCE_BETWEEN_WHEELS_MM);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = readHexFloat6(inputStream, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->coderWheelDistanceBetweenWheelsMM =  value;
    }
    else if (commandHeader == COMMAND_SET_CODER_WHEEL_PULSE_BY_ROTATION) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_CODER_WHEEL_PULSE_BY_ROTATION);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = readHexFloat6(inputStream, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->coderWheelPulseByRotation = value;
    }
    // MOTOR PART
    else if (commandHeader == COMMAND_SET_MOTOR_WHEEL_AVERAGE_DIAMETER_MM) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_MOTOR_WHEEL_AVERAGE_DIAMETER_MM);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = readHexFloat6(inputStream, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->motorWheelAverageDiameterMM = value;
    }
    else if (commandHeader == COMMAND_SET_MOTOR_DISTANCE_BETWEEN_WHEELS_MM) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_MOTOR_DISTANCE_BETWEEN_WHEELS_MM);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = readHexFloat6(inputStream, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->motorWheelDistanceBetweenWheelsMM = value;
    }
    else if (commandHeader == COMMAND_SET_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_MOTOR_WHEEL_ROTATION_BY_SECONDS_AT_FULL_SPEED);
        RobotKinematics* robotKinematics = getRobotKinematics();
        float value = readHexFloat6(inputStream, ROBOT_KINEMATICS_DEFAULT_DIGIT_PRECISION);
        robotKinematics->motorWheelRotationBySecondAtFullSpeed = value;
    }
    // ROBOT TYPE
    else if (commandHeader == COMMAND_SET_ROBOT_TYPE) {
        ackCommand(outputStream, KINEMATICS_HEADER, COMMAND_SET_ROBOT_TYPE);
        RobotKinematics* robotKinematics = getRobotKinematics();
        enum RobotType robotType = readHex2(inputStream);
        robotKinematics->robotType = robotType;
    }
    // TODO : END OF MOTOR PART + ROBOT PART
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
