#include "motionDriver.h"

#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../device/motion/simple/motionDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

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

bool motionDriverGotoPositionPulse(float left,
							        float right,
							        float a,
							        float s) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_GOTO_IN_PULSE);
    appendHex4(outputStream, left);
    appendHex4(outputStream, right);
    appendHex2(outputStream, a);
    appendHex2(outputStream, s);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool motionDriverForward(float distanceInMM) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_FORWARD_IN_MM);
    appendHex4(outputStream, distanceInMM);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool motionDriverMaintainPosition() {
    bool result = motionDriverForward(0.0f);

    return result;
}

bool motionDriverBackward(float distanceInMM) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_BACKWARD_IN_MM);
    appendHex4(outputStream, distanceInMM);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool motionDriverLeft(float leftDeciDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_LEFT_IN_DECI_DEGREE);
    appendHex4(outputStream, leftDeciDegree);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool motionDriverRight(float rightDeciDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_RIGHT_IN_DECI_DEGREE);
    appendHex4(outputStream, rightDeciDegree);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// ONLY ONE WHEEL

bool motionDriverLeftOneWheel(float leftDeciDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE);
    appendHex4(outputStream, leftDeciDegree);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool motionDriverRightOneWheel(float rightDeciDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE);
    appendHex4(outputStream, rightDeciDegree);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// B-SPLINE MOTION

bool motionDriverBSplineRelative(float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor) {
	OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_SPLINE_RELATIVE);
    appendHex4(outputStream, x);
	appendSeparator(outputStream);
    appendHex4(outputStream, y);
	appendSeparator(outputStream);
    appendHex4(outputStream, angle);
	appendSeparator(outputStream);
    appendHex2(outputStream, dist0);
	appendSeparator(outputStream);
    appendHex2(outputStream, dist1);
	appendSeparator(outputStream);
    appendHex(outputStream, accelerationFactor);
    appendHex(outputStream, speedFactor);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool motionDriverBSplineAbsolute(float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor) {
	OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_SPLINE_ABSOLUTE);
    appendHex4(outputStream, x);
	appendSeparator(outputStream);
    appendHex4(outputStream, y);
	appendSeparator(outputStream);
    appendHex4(outputStream, angle);
	appendSeparator(outputStream);
    appendHex2(outputStream, dist0);
	appendSeparator(outputStream);
    appendHex2(outputStream, dist1);
	appendSeparator(outputStream);
    appendHex(outputStream, accelerationFactor);
    appendHex(outputStream, speedFactor);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// STOP

bool motionDriverStop() {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_CANCEL);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// OBSTACLE

bool motionDriverObstacle() {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_OBSTACLE);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// SET MOTION PARAMETERS

bool motionSetParameters(int motionType, int a, int speed) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_SET_MOTION_PARAMETERS);
    appendHex2(outputStream, motionType);
    appendHex2(outputStream, a);
    appendHex2(outputStream, speed);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

