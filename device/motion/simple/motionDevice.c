#include "motionDevice.h"
#include "motionDeviceInterface.h"

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"
#include "../../../common/io/stream.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"

#include "../../../device/device.h"
#include "../../../device/motion/position/trajectoryDevice.h"

// #include "../../../motion/extended/bsplineDebug.h"
#include "../../../motion/simple/motion.h"
#include "../../../motion/simple/motionPersistence.h"
#include "../../../motion/pid/pid.h"
#include "../../../motion/pid/pidTimer.h"
#include "../../../motion/position/trajectory.h"


void deviceMotionInit() {
    loadMotionParameters();
}

void deviceMotionShutDown() {
}

BOOL deviceMotionIsOk() {
    return TRUE;
}

void notifyPosition() {

}

void internalDebugNotify(char* notifyString) {
    OutputStream* outputStream = getDebugOutputStreamLogger();
    appendString(outputStream, "Motion ");
    appendString(outputStream, notifyString);
    appendString(outputStream, "t=");
    appendDec(outputStream, getPidTime());
    appendString(outputStream, ")\n");
}

void notifyReached(OutputStream* outputStream) {
    append(outputStream, NOTIFY_MOTION_STATUS);
    appendHex2(outputStream, NOTIFY_MOTION_ARG_REACHED);

    // send position
    appendSeparator(outputStream);
    notifyAbsolutePositionWithoutHeader(outputStream);

    // internalDebugNotify("reached");
}

void notifyFailed(OutputStream* outputStream) {
    append(outputStream, NOTIFY_MOTION_STATUS);
    appendHex2(outputStream, NOTIFY_MOTION_ARG_FAILED);

    // send position
    appendSeparator(outputStream);
    notifyAbsolutePositionWithoutHeader(outputStream);

    // internalDebugNotify("failed");
}

void notifyMoving(OutputStream* outputStream) {
    append(outputStream, NOTIFY_MOTION_STATUS);
    appendHex2(outputStream, NOTIFY_MOTION_ARG_MOVING);

    // send position
    appendSeparator(outputStream);
    notifyAbsolutePositionWithoutHeader(outputStream);

    internalDebugNotify("moving");
}

void notifyObstacle(OutputStream* outputStream) {
    append(outputStream, NOTIFY_MOTION_STATUS);
    appendHex2(outputStream, NOTIFY_MOTION_ARG_OBSTACLE);

    // send position
    appendSeparator(outputStream);
    notifyAbsolutePositionWithoutHeader(outputStream);

    internalDebugNotify("obstacle");
}

void deviceMotionHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    // GOTO in impulsion
    if (header == COMMAND_MOTION_GOTO_IN_PULSE) {
        // send acquittement
        appendAck(outputStream);

        // Ex: 000100 000100 01 10
        // Left position
        long left = readHex6(inputStream);
        // Right position
        long right = readHex6(inputStream);
        // Acceleration
        char a = readHex2(inputStream);
        // Speed
        char s = readHex2(inputStream);

        // Execute Motion
        gotoPosition(left, right, (float) a, (float) s);

        append(outputStream, COMMAND_MOTION_GOTO_IN_PULSE);
    }        // "forward" in millimeter
    else if (header == COMMAND_MOTION_FORWARD_IN_MM) {
        appendAck(outputStream);
		append(outputStream, COMMAND_MOTION_FORWARD_IN_MM);

        long distanceMM = readHex4(inputStream);
        forwardSimpleMM(distanceMM);

        
    }        // "backward" in millimeter
    else if (header == COMMAND_MOTION_BACKWARD_IN_MM) {
        appendAck(outputStream);
		append(outputStream, COMMAND_MOTION_BACKWARD_IN_MM);

        long distanceMM = readHex4(inputStream);
        backwardSimpleMM(distanceMM);
    }        // ROTATION
        // -> left
    else if (header == COMMAND_MOTION_LEFT_IN_DECI_DEGREE) {
        appendAck(outputStream);

        long leftDegree = readHex4(inputStream);
        leftSimpleDegree(leftDegree);

        append(outputStream, COMMAND_MOTION_LEFT_IN_DECI_DEGREE);
    }        // -> right
    else if (header == COMMAND_MOTION_RIGHT_IN_DECI_DEGREE) {
        appendAck(outputStream);

        long rightDegree = readHex4(inputStream);
        rightSimpleDegree(rightDegree);

        append(outputStream, COMMAND_MOTION_RIGHT_IN_DECI_DEGREE);
    }        // ONE WHEEL
        // -> left
    else if (header == COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE) {
        appendAck(outputStream);

        long leftDegree = readHex4(inputStream);
        leftOneWheelSimpleDegree(leftDegree);

        append(outputStream, COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE);
    }        // -> right
    else if (header == COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE) {
        appendAck(outputStream);

        long rightDegree = readHex4(inputStream);
        rightOneWheelSimpleDegree(rightDegree);

        append(outputStream, COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE);
    }        // -> bspline
    else if (header == COMMAND_MOTION_SPLINE_RELATIVE || header == COMMAND_MOTION_SPLINE_ABSOLUTE) {
        appendAck(outputStream);

        float x = (float) readHex4(inputStream);
        checkIsChar(inputStream, '-');

        float y = (float) readHex4(inputStream);
        checkIsChar(inputStream, '-');

		float angle = readHex4(inputStream);
		angle = angle * PI_DIVIDE_1800;
		checkIsChar(inputStream, '-');

		// the distance can be negative, so the robot go back instead of go forward
		// Distance1 in cm
		float distance1 = readSignedHex2(inputStream);
		checkIsChar(inputStream, '-');
		distance1 *= 10.0f;
	
		// the distance can be negative, so the robot go back instead of go forward
		// Distance2 in cm
		float distance2 = readSignedHex2(inputStream);
		distance2 *= 10.0f;

		checkIsChar(inputStream, '-');
		int accelerationFactor = readHex(inputStream);
		int speedFactor = readHex(inputStream);

		// if distance = 0, the system computes the optimum distance
		// we use relative
        gotoSimpleSpline(x, y,
						angle, 
						distance1, distance2, 
						accelerationFactor, speedFactor,
						header == COMMAND_MOTION_SPLINE_RELATIVE
						);

        append(outputStream, header);
    }
    else if (header == COMMAND_MOTION_SPLINE_TEST_LEFT || header == COMMAND_MOTION_SPLINE_TEST_RIGHT) {
        appendAck(outputStream);
		float sign = 1.0f;
		if (header == COMMAND_MOTION_SPLINE_TEST_RIGHT) {
			sign = -sign;
		}
		gotoSimpleSpline(400.0f, sign * 400.0f,
						 sign * 0.75f * PI,
						 200.0f, 200.0f,
						MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL,
						 TRUE);
        append(outputStream, header);
    }
	// STOP
        // cancel motion
    else if (header == COMMAND_MOTION_CANCEL) {
        appendAck(outputStream);

        stopPosition(FALSE);
		clearMotionDefinitionList();

        append(outputStream, COMMAND_MOTION_CANCEL);
    }        // OBSTACLE
        // cancel motion
    else if (header == COMMAND_MOTION_OBSTACLE) {
        // TODO : A REVOIR
        appendAck(outputStream);
        stopPosition(TRUE);

        append(outputStream, COMMAND_MOTION_OBSTACLE);
        notifyObstacle(outputStream);
    }        // CALIBRATION
    else if (header == COMMAND_SQUARE_CALIBRATION) {
        appendAck(outputStream);
		unsigned char type = readHex2(inputStream);
		unsigned int length = readHex4(inputStream);
        squareCalibration(type, length);
        append(outputStream, COMMAND_SQUARE_CALIBRATION);
    }        // PARAMETERS
    else if (header == COMMAND_GET_MOTION_PARAMETERS) {
        appendAck(outputStream);
        int motionType = readHex2(inputStream);

        append(outputStream, COMMAND_GET_MOTION_PARAMETERS);
        MotionParameter* motionParameter = getDefaultMotionParameters(motionType);
        appendHex2(outputStream, motionParameter->a);
        appendHex2(outputStream, motionParameter->speed);

    } else if (header == COMMAND_SET_MOTION_PARAMETERS) {
        appendAck(outputStream);
        int motionType = readHex2(inputStream);
        int a = readHex2(inputStream);
        int speed = readHex2(inputStream);

        MotionParameter* motionParameter = getDefaultMotionParameters(motionType);
        motionParameter->a = a;
        motionParameter->speed = speed;

        saveMotionParameters();

        append(outputStream, COMMAND_SET_MOTION_PARAMETERS);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceMotionInit,
    .deviceShutDown = &deviceMotionShutDown,
    .deviceIsOk = &deviceMotionIsOk,
    .deviceHandleRawData = &deviceMotionHandleRawData,
};

DeviceDescriptor* getMotionDeviceDescriptor() {
    return &descriptor;
}
