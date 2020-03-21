#include <stdbool.h>

#include "motionSimulationDevice.h"
#include "motionSimulationDeviceInterface.h"

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../device/device.h"

#include "../../../motion/simulation/motionSimulation.h"

void deviceMotionSimulationInit(void) {

}

void deviceMotionSimulationShutDown(void) {
}

bool deviceMotionSimulationIsOk(void) {
    return true;
}

void deviceMotionSimulationHandleRawData(unsigned char commandHeader,
        InputStream* inputStream,
        OutputStream* outputStream,
        OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_MOTION_SIMULATION_GET) {
        // send acknowledge
        ackCommand(outputStream, MOTION_SIMULATION_DEVICE_HEADER, COMMAND_MOTION_SIMULATION_GET);

        MotionSimulationParameter* motionSimulationParameter = getMotionSimulationParameter();

        appendHex(outputStream, motionSimulationParameter->simulateMotors);
        appendHex(outputStream, motionSimulationParameter->simulateCoders);
        appendHex(outputStream, motionSimulationParameter->simulateRobotPosition);
    } else if (commandHeader == COMMAND_MOTION_SIMULATION_SET) {
        // send acknowledge
        ackCommand(outputStream, MOTION_SIMULATION_DEVICE_HEADER, COMMAND_MOTION_SIMULATION_SET);

        bool simulateMotors = readHex(inputStream);
        bool simulateCoders = readHex(inputStream);
        bool simulateRobotPosition = readHex(inputStream);

        MotionSimulationParameter* motionSimulationParameter = getMotionSimulationParameter();
        motionSimulationParameter->simulateMotors = simulateMotors;
        motionSimulationParameter->simulateCoders = simulateCoders;
        motionSimulationParameter->simulateRobotPosition = simulateRobotPosition;
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceMotionSimulationInit,
    .deviceShutDown = &deviceMotionSimulationShutDown,
    .deviceIsOk = &deviceMotionSimulationIsOk,
    .deviceHandleRawData = &deviceMotionSimulationHandleRawData,
};

DeviceDescriptor* getMotionSimulationDeviceDescriptor() {
    return &descriptor;
}
