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

static BOOL readyForNextMotion = FALSE;

static unsigned int motionIndex = 0;

void setReadyForNextMotion(BOOL value) {
    readyForNextMotion = value;
}

BOOL isReadyForNextMotion() {
    return readyForNextMotion;
}

void incMotionInstructionIndex() {
    motionIndex++;
}

unsigned int getMotionInstructionIndex() {
    return motionIndex;
}

// GO / ROTATE MOTION

BOOL motionDriverGotoPositionPulse(float left,
							        float right,
							        float a,
							        float s) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_GOTO_IN_PULSE);
    appendHex4(outputStream, left);
    appendHex4(outputStream, right);
    appendHex2(outputStream, a);
    appendHex2(outputStream, s);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

BOOL motionDriverForward(float distanceInMM) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_FORWARD_IN_MM);
    appendHex4(outputStream, distanceInMM);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

BOOL motionDriverMaintainPosition() {
    BOOL result = motionDriverForward(0.0f);

    return result;
}

BOOL motionDriverBackward(float distanceInMM) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_BACKWARD_IN_MM);
    appendHex4(outputStream, distanceInMM);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

BOOL motionDriverLeft(float leftDeciDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_LEFT_IN_DECI_DEGREE);
    appendHex4(outputStream, leftDeciDegree);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

BOOL motionDriverRight(float rightDeciDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_RIGHT_IN_DECI_DEGREE);
    appendHex4(outputStream, rightDeciDegree);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

// ONLY ONE WHEEL

BOOL motionDriverLeftOneWheel(float leftDeciDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE);
    appendHex4(outputStream, leftDeciDegree);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

BOOL motionDriverRightOneWheel(float rightDeciDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE);
    appendHex4(outputStream, rightDeciDegree);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

// B-SPLINE MOTION

BOOL motionDriverBSplineRelative(float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor) {
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

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

BOOL motionDriverBSplineAbsolute(float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor) {
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

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

// STOP

BOOL motionDriverStop() {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_CANCEL);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

// OBSTACLE

BOOL motionDriverObstacle() {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_MOTION_OBSTACLE);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

// SET MOTION PARAMETERS

BOOL motionSetParameters(int motionType, int a, int speed) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_SET_MOTION_PARAMETERS);
    appendHex2(outputStream, motionType);
    appendHex2(outputStream, a);
    appendHex2(outputStream, speed);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}

