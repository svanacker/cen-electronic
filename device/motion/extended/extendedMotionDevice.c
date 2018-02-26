#include <stdbool.h>

#include "extendedMotionDevice.h"
#include "extendedMotionDeviceInterface.h"

#include "../../../common/commons.h"

#include "../../../common/cmd/commonCommand.h"

#include "../../../common/eeprom/eeprom.h"

#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logLevel.h"

#include "../../../common/math/cenMath.h"

#include "../../../device/device.h"
#include "../../../device/motion/position/trajectoryDevice.h"

#include "../../../motion/parameters/motionParameterType.h"
#include "../../../motion/parameters/motionParameter.h"
#include "../../../motion/parameters/motionPersistence.h"

#include "../../../motion/motion.h"
#include "../../../motion/extended/bsplineMotion.h"

#include "../../../motion/pid/detectedMotionType.h"
#include "../../../motion/pid/pidType.h"
#include "../../../motion/pid/pidTimer.h"

#include "../../../motion/position/trajectory.h"

static PidMotion* pidMotion;

void deviceExtendedMotionInit(void) {
    loadMotionParameters(pidMotion->pidPersistenceEeprom, true);
}

void deviceExtendedMotionShutDown(void) {
}

bool deviceExtendedMotionIsOk(void) {
    return true;
}

void deviceExtendedMotionHandleRawData(char commandHeader,
        InputStream* inputStream,
        OutputStream* outputStream,
        OutputStream* notificationOutputStream) {
	// -> bspline
    if (commandHeader == COMMAND_MOTION_SPLINE_RELATIVE || commandHeader == COMMAND_MOTION_SPLINE_ABSOLUTE) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, commandHeader);

        float x = (float) readHex4(inputStream);
        checkIsSeparator(inputStream);

        float y = (float) readHex4(inputStream);
        checkIsSeparator(inputStream);

        float angle = (float) readHex4(inputStream);
        angle = angle * PI_DIVIDE_1800;
        checkIsSeparator(inputStream);

        // the distance can be negative, so the robot go back instead of go forward
        float distance1 = (float) readSignedHex4(inputStream);
        checkIsSeparator(inputStream);
    
        // the distance can be negative, so the robot go back instead of go forward
        float distance2 = (float) readSignedHex4(inputStream);

        checkIsSeparator(inputStream);
        int accelerationFactor = readHex(inputStream);
        int speedFactor = readHex(inputStream);

        // if distance = 0, the system computes the optimum distance
        // we use relative
        gotoSimpleSpline(pidMotion,
						x, y,
                        angle, 
                        distance1, distance2, 
                        accelerationFactor, speedFactor,
                        commandHeader == COMMAND_MOTION_SPLINE_RELATIVE,
					    notificationOutputStream
                        );
    }
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_LEFT || commandHeader == COMMAND_MOTION_SPLINE_TEST_RIGHT) {
        ackCommand(outputStream, MOTION_DEVICE_HEADER, commandHeader);
        float sign = 1.0f;
        if (commandHeader == COMMAND_MOTION_SPLINE_TEST_RIGHT) {
            sign = -sign;
        }
        gotoSimpleSpline(pidMotion,
						 400.0f, sign * 400.0f,
                         sign * 0.75f * PI,
                         200.0f, 200.0f,
                        MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL,
                         true,
					    notificationOutputStream);
    }
 }

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceExtendedMotionInit,
    .deviceShutDown = &deviceExtendedMotionShutDown,
    .deviceIsOk = &deviceExtendedMotionIsOk,
    .deviceHandleRawData = &deviceExtendedMotionHandleRawData,
};

DeviceDescriptor* getExtendedMotionDeviceDescriptor(PidMotion* pidMotionParam) {
	pidMotion = pidMotionParam;
    return &descriptor;
}
