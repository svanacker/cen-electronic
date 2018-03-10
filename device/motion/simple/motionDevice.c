#include <stdbool.h>

#include "motionDevice.h"
#include "motionDeviceInterface.h"

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/eeprom/eeprom.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/printTableWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"

#include "../../../device/device.h"
#include "../../../device/motion/position/trajectoryDevice.h"

#include "../../../motion/parameters/motionParameterType.h"
#include "../../../motion/parameters/motionParameter.h"
#include "../../../motion/parameters/motionParameterPersistence.h"

#include "../../../motion/motion.h"
#include "../../../motion/simple/simpleMotion.h"
#include "../../../motion/simple/motionCalibration.h"

#include "../../../motion/pid/detectedMotionType.h"
#include "../../../motion/pid/pidMotion.h"
#include "../../../motion/pid/pidType.h"
#include "../../../motion/pid/pidTimer.h"


#include "../../../motion/position/trajectory.h"

static PidMotion* pidMotion;

void deviceMotionInit(void) {
    loadMotionParameters(pidMotion->pidPersistenceEeprom, false);
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
	if (outputStream == NULL) {
		return;
	}
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, NOTIFY_MOTION_STATUS_REACHED);

    // send position
    appendSeparator(outputStream);
    notifyAbsolutePositionWithoutHeader(outputStream);

    // internalDebugNotify("reached");
}

void notifyFailed(OutputStream* outputStream) {
	if (outputStream == NULL) {
		return;
	}
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, NOTIFY_MOTION_STATUS_FAILED);

    // send position
    appendSeparator(outputStream);
    notifyAbsolutePositionWithoutHeader(outputStream);

    // internalDebugNotify("failed");
}

void notifyMoving(OutputStream* outputStream) {
	if (outputStream == NULL) {
		return;
	}
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, NOTIFY_MOTION_STATUS_MOVING);

    // send position
    appendSeparator(outputStream);
    notifyAbsolutePositionWithoutHeader(outputStream);

    internalDebugNotify("moving");
}

void notifyObstacle(OutputStream* outputStream) {
	if (outputStream == NULL) {
		return;
	}
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, NOTIFY_MOTION_STATUS_OBSTACLE);

    // send position
    appendSeparator(outputStream);
    notifyAbsolutePositionWithoutHeader(outputStream);

    internalDebugNotify("obstacle");
}


void deviceMotionHandleRawData(char commandHeader,
        InputStream* inputStream,
        OutputStream* outputStream,
        OutputStream* notificationOutputStream) {
    // "forward" in millimeter
    if (commandHeader == COMMAND_MOTION_FORWARD_IN_MM) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_FORWARD_IN_MM);

        float distanceMM = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        forwardSimpleMM(pidMotion, distanceMM, notificationOutputStream);
    }        // "backward" in millimeter
    else if (commandHeader == COMMAND_MOTION_BACKWARD_IN_MM) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_BACKWARD_IN_MM);

        float distanceMM = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        backwardSimpleMM(pidMotion, distanceMM, notificationOutputStream);
    }        // ROTATION
        // -> left
    else if (commandHeader == COMMAND_MOTION_LEFT_IN_DECI_DEGREE) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_LEFT_IN_DECI_DEGREE);

        float leftDegree = readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION);
        leftSimpleDegree(pidMotion, leftDegree, notificationOutputStream);
    }        // -> right
    else if (commandHeader == COMMAND_MOTION_RIGHT_IN_DECI_DEGREE) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_RIGHT_IN_DECI_DEGREE);

        float rightDegree = readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION);
        rightSimpleDegree(pidMotion, rightDegree, notificationOutputStream);
    }        // ONE WHEEL
        // -> left
    else if (commandHeader == COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_LEFT_ONE_WHEEL_IN_DECI_DEGREE);

        float leftDegree = readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION);
        leftOneWheelSimpleDegree(pidMotion, leftDegree, notificationOutputStream);
    }        // -> right
    else if (commandHeader == COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_RIGHT_ONE_WHEEL_IN_DECI_DEGREE);

        float rightDegree = readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION);
        rightOneWheelSimpleDegree(pidMotion, rightDegree, notificationOutputStream);
    }
    // STOP
        // stop/cancel motion
    else if (commandHeader == COMMAND_MOTION_STOP) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_STOP);

        stopPosition(pidMotion, false, notificationOutputStream);
    }
    else if (commandHeader == COMMAND_MOTION_CANCEL_ALL) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_CANCEL_ALL);
		clearPidMotion(pidMotion);
        stopPosition(pidMotion, false, notificationOutputStream);
    }
	// OBSTACLE
    else if (commandHeader == COMMAND_MOTION_OBSTACLE) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_OBSTACLE);
        // TODO : A REVOIR
        stopPosition(pidMotion, true, notificationOutputStream);
    }        // CALIBRATION
    else if (commandHeader == COMMAND_SQUARE_CALIBRATION) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_SQUARE_CALIBRATION);
        unsigned char type = readHex2(inputStream);
        checkIsSeparator(inputStream);
        float length = (float) readHex4(inputStream);
        squareCalibration(pidMotion, type, length, notificationOutputStream);
    }        // PARAMETERS

	// MODE
	else if (commandHeader == COMMAND_MOTION_MODE_ADD) {
		ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_MODE_ADD);
		setMotionModeAdd(pidMotion);
	}
	else if (commandHeader == COMMAND_MOTION_MODE_REPLACE) {
		ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_MODE_REPLACE);
		setMotionModeReplace(pidMotion);
	}
	else if (commandHeader == COMMAND_MOTION_MODE_GET) {
		ackCommand(outputStream, MOTION_DEVICE_HEADER, COMMAND_MOTION_MODE_GET);
		bool stacked = isStackMotionDefinitions(pidMotion);
		appendBool(outputStream, stacked);
	}
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceMotionInit,
    .deviceShutDown = &deviceMotionShutDown,
    .deviceIsOk = &deviceMotionIsOk,
    .deviceHandleRawData = &deviceMotionHandleRawData,
};

DeviceDescriptor* getMotionDeviceDescriptor(PidMotion* pidMotionParam) {
	pidMotion = pidMotionParam;
    return &descriptor;
}
