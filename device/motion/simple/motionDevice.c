#include <stdbool.h>

#include "motionDevice.h"
#include "motionDeviceInterface.h"

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"

#include "../../../device/device.h"
#include "../../../device/motion/position/trajectoryDevice.h"

#include "../../../motion/simple/motion.h"
#include "../../../motion/simple/motionPersistence.h"
#include "../../../motion/pid/pidTimer.h"
#include "../../../motion/position/trajectory.h"


void deviceMotionInit(void) {
    loadMotionParameters();
}

void deviceMotionShutDown(void) {
}

bool deviceMotionIsOk(void) {
    return true;
}

void notifyPosition(void) {

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
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, NOTIFY_MOTION_STATUS_REACHED);

    // send position
    appendSeparator(outputStream);
    notifyAbsolutePositionWithoutHeader(outputStream);

    // internalDebugNotify("reached");
}

void notifyFailed(OutputStream* outputStream) {
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, NOTIFY_MOTION_STATUS_FAILED);

    // send position
    appendSeparator(outputStream);
    notifyAbsolutePositionWithoutHeader(outputStream);

    // internalDebugNotify("failed");
}

void notifyMoving(OutputStream* outputStream) {
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, NOTIFY_MOTION_STATUS_MOVING);

    // send position
    appendSeparator(outputStream);
    notifyAbsolutePositionWithoutHeader(outputStream);

    internalDebugNotify("moving");
}

void notifyObstacle(OutputStream* outputStream) {
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, NOTIFY_MOTION_STATUS_OBSTACLE);

    // send position
    appendSeparator(outputStream);
    notifyAbsolutePositionWithoutHeader(outputStream);

    internalDebugNotify("obstacle");
}

void deviceMotionHandleRawData(char commandHeader,
        InputStream* inputStream,
        OutputStream* outputStream) {
    // GOTO in impulsion
    if (commandHeader == COMMAND_MOTION_GOTO_IN_PULSE) {
        // send acknowledge
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_GOTO_IN_PULSE);

        // Ex: 000100 000100 01 10
        // Left position
        float left = (float) readHex6(inputStream);
        // Right position
        float right = (float) readHex6(inputStream);
        // Acceleration
        float a = (float) readHex2(inputStream);
        // Speed
        float s = (float) readHex2(inputStream);

        // Execute Motion
        gotoPosition(left, right, a, s);
    }        // "forward" in millimeter
    else if (commandHeader == COMMAND_MOTION_FORWARD_IN_MM) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_FORWARD_IN_MM);

        float distanceMM = (float) readHex4(inputStream);
        forwardSimpleMM(distanceMM);
    }        // "backward" in millimeter
    else if (commandHeader == COMMAND_MOTION_BACKWARD_IN_MM) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_BACKWARD_IN_MM);

        float distanceMM = (float) readHex4(inputStream);
        backwardSimpleMM(distanceMM);
    }        // ROTATION
        // -> left
    else if (commandHeader == COMMAND_MOTION_LEFT_IN_DECI_DEGREE) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_LEFT_IN_DECI_DEGREE);

        float leftDegree = (float) readHex4(inputStream);
        leftSimpleDegree(leftDegree);
    }        // -> right
    else if (commandHeader == COMMAND_MOTION_RIGHT_IN_DECI_DEGREE) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_RIGHT_IN_DECI_DEGREE);

        float rightDegree = (float) readHex4(inputStream);
        rightSimpleDegree(rightDegree);
    }        // ONE WHEEL
        // -> left
    else if (commandHeader == COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE);

        float leftDegree = (float) readHex4(inputStream);
        leftOneWheelSimpleDegree(leftDegree);
    }        // -> right
    else if (commandHeader == COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE);

        float rightDegree = (float) readHex4(inputStream);
        rightOneWheelSimpleDegree(rightDegree);
    }        // -> bspline
    else if (commandHeader == COMMAND_MOTION_SPLINE_RELATIVE || commandHeader == COMMAND_MOTION_SPLINE_ABSOLUTE) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, commandHeader);

        float x = (float) readHex4(inputStream);
        checkIsChar(inputStream, '-');

        float y = (float) readHex4(inputStream);
        checkIsChar(inputStream, '-');

        float angle = (float) readHex4(inputStream);
        angle = angle * PI_DIVIDE_1800;
        checkIsChar(inputStream, '-');

        // the distance can be negative, so the robot go back instead of go forward
        // Distance1 in cm
        float distance1 = (float) readSignedHex2(inputStream);
        checkIsChar(inputStream, '-');
        distance1 *= 10.0f;
    
        // the distance can be negative, so the robot go back instead of go forward
        // Distance2 in cm
        float distance2 = (float) readSignedHex2(inputStream);
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
                        commandHeader == COMMAND_MOTION_SPLINE_RELATIVE
                        );
    }
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_LEFT || commandHeader == COMMAND_MOTION_SPLINE_TEST_RIGHT) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, commandHeader);
        float sign = 1.0f;
        if (commandHeader == COMMAND_MOTION_SPLINE_TEST_RIGHT) {
            sign = -sign;
        }
        gotoSimpleSpline(400.0f, sign * 400.0f,
                         sign * 0.75f * PI,
                         200.0f, 200.0f,
                        MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL,
                         true);
        append(outputStream, commandHeader);
    }
    // STOP
        // cancel motion
    else if (commandHeader == COMMAND_MOTION_CANCEL) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_CANCEL);

        stopPosition(false);
    }        // OBSTACLE
        // cancel motion
    else if (commandHeader == COMMAND_MOTION_OBSTACLE) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_OBSTACLE);
        // TODO : A REVOIR
        stopPosition(true);

        notifyObstacle(outputStream);
    }        // CALIBRATION
    else if (commandHeader == COMMAND_SQUARE_CALIBRATION) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_SQUARE_CALIBRATION);
        unsigned char type = readHex2(inputStream);
        float length = (float) readHex4(inputStream);
        squareCalibration(type, length);
    }        // PARAMETERS
    else if (commandHeader == COMMAND_GET_MOTION_PARAMETERS) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_GET_MOTION_PARAMETERS);
        int motionType = readHex2(inputStream);

        MotionParameter* motionParameter = getDefaultMotionParameters(motionType);
        appendHex2(outputStream, (int) motionParameter->a);
        appendHex2(outputStream, (int) motionParameter->speed);

    } else if (commandHeader == COMMAND_SET_MOTION_PARAMETERS) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_SET_MOTION_PARAMETERS);
        int motionType = readHex2(inputStream);
        float a = (float) readHex2(inputStream);
        float speed = (float) readHex2(inputStream);

        MotionParameter* motionParameter = getDefaultMotionParameters(motionType);
        motionParameter->a = a;
        motionParameter->speed = speed;

        saveMotionParameters();
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceMotionInit,
    .deviceShutDown = &deviceMotionShutDown,
    .deviceIsOk = &deviceMotionIsOk,
    .deviceHandleRawData = &deviceMotionHandleRawData,
};

DeviceDescriptor* getMotionDeviceDescriptor(void) {
    return &descriptor;
}
