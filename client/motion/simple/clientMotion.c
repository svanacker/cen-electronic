#include "clientMotion.h"

#include "../../../common/2d/2d.h"
#include "../../../common/commons.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/ioUtils.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logHandler.h"

#include "../../../motion/parameters/motionParameter.h"

#include "../../../device/motion/simple/motionDeviceInterface.h"
#include "../../../device/motion/pid/pidDeviceInterface.h"

#include "../../../drivers/driver.h"
#include "../../../drivers/driverList.h"
#include "../../../drivers/driverTransmitter.h"

static bool readyForNextMotion = false;

static unsigned char motionIndex = 0;

void setReadyForNextMotion(bool value) {
    readyForNextMotion = value;
}

bool isReadyForNextMotion() {
    return readyForNextMotion;
}

void incMotionInstructionIndex() {
    motionIndex++;
}

unsigned int getMotionInstructionIndex() {
    return motionIndex;
}

// GO / ROTATE MOTION

bool motionDriverForward(float distanceInMM) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_MOTION_FORWARD_IN_MM);
    appendHexFloat4(outputStream, distanceInMM, POSITION_DIGIT_MM_PRECISION);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool motionDriverMaintainPosition() {
    bool result = motionDriverForward(0.0f);

    return result;
}

bool motionDriverBackward(float distanceInMM) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_MOTION_BACKWARD_IN_MM);
    appendHexFloat4(outputStream, distanceInMM, POSITION_DIGIT_MM_PRECISION);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool motionDriverLeft(float leftDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_MOTION_LEFT_IN_DECI_DEGREE);
    appendHexFloat4(outputStream, leftDegree, ANGLE_DIGIT_DEGREE_PRECISION);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool motionDriverRight(float rightDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_MOTION_RIGHT_IN_DECI_DEGREE);
    appendHexFloat4(outputStream, rightDegree, ANGLE_DIGIT_DEGREE_PRECISION);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// ONLY ONE WHEEL

bool motionDriverLeftOneWheel(float leftDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE);
    appendHexFloat4(outputStream, leftDegree, ANGLE_DIGIT_DEGREE_PRECISION);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool motionDriverRightOneWheel(float rightDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE);
    appendHexFloat4(outputStream, rightDegree, ANGLE_DIGIT_DEGREE_PRECISION);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// STOP

bool motionDriverStop() {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_MOTION_STOP);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// OBSTACLE

bool motionDriverObstacle() {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_MOTION_OBSTACLE);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// SET MOTION PARAMETERS

bool motionSetParameters(int motionType, float a, float speed) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_SET_MOTION_PARAMETERS);
    appendHex2(outputStream, motionType);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, a, MOTION_PARAMETERS_ACCELERATION_DIGIT);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, speed, MOTION_PARAMETERS_SPEED_DIGIT);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

