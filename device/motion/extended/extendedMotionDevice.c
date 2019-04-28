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
#include "../../../motion/parameters/motionParameterPersistence.h"

#include "../../../motion/motion.h"
#include "../../../motion/extended/bsplineMotion.h"

#include "../../../motion/pid/detectedMotionType.h"
#include "../../../motion/pid/pidType.h"
#include "../../../motion/pid/pidTimer.h"

#include "../../../motion/position/trajectory.h"

static PidMotion* pidMotion;

void deviceExtendedMotionInit(void) {
    Eeprom* eeprom_ = pidMotion->pidPersistenceEeprom;
    if (eeprom_->eepromType == EEPROM_TYPE_MEMORY) {
        loadMotionParameters(eeprom_, true);
        // We store to do as it was already previously store !
        saveMotionParameters(eeprom_);
    }
    else {
        loadMotionParameters(eeprom_, false);
    }
}

void deviceExtendedMotionShutDown(void) {
}

bool deviceExtendedMotionIsOk(void) {
    return true;
}

void deviceExtendedMotionHandleRawData(unsigned char commandHeader,
        InputStream* inputStream,
        OutputStream* outputStream,
        OutputStream* notificationOutputStream) {
	// -> bspline
    if (commandHeader == COMMAND_MOTION_SPLINE_RELATIVE || commandHeader == COMMAND_MOTION_SPLINE_ABSOLUTE) {
        ackCommand(outputStream, EXTENDED_MOTION_DEVICE_HEADER, commandHeader);

        float x = readHexFloat6(inputStream, POSITION_DIGIT_MM_PRECISION);
        checkIsSeparator(inputStream);

        float y = readHexFloat6(inputStream, POSITION_DIGIT_MM_PRECISION);
        checkIsSeparator(inputStream);

        float angleInDegree = readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION);
        float angleRadian = degToRad(angleInDegree);
        checkIsSeparator(inputStream);

        // the distance can be negative, so the robot go back instead of go forward
        float distance1 = readHexFloat4(inputStream, BSPLINE_MOTION_DISTANCE_FACTOR_DIGIT);
        checkIsSeparator(inputStream);
    
        // the distance can be negative, so the robot go back instead of go forward
        float distance2 = readHexFloat4(inputStream, BSPLINE_MOTION_DISTANCE_FACTOR_DIGIT);
        checkIsSeparator(inputStream);

        // Factors
        float accelerationFactor = readHexFloat2(inputStream, BSPLINE_MOTION_ACCELERATION_FACTOR_DIGIT);
        checkIsSeparator(inputStream);
        float speedFactor = readHexFloat2(inputStream, BSPLINE_MOTION_SPEED_FACTOR_DIGIT);

        // if distance = 0, the system computes the optimum distance
        // we use relative
        gotoSpline(pidMotion,
						x, y,
                        angleRadian,
                        distance1, distance2, 
                        accelerationFactor, speedFactor,
                        commandHeader == COMMAND_MOTION_SPLINE_RELATIVE,
					    notificationOutputStream
                        );
    }
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_FORWARD) {
        ackCommand(outputStream, EXTENDED_MOTION_DEVICE_HEADER, commandHeader);
        gotoSpline(pidMotion,
                 400.0f, 0.0f,
                 0.0f,
                 100.0f, 100.0f,
                MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL,
                 true,
                notificationOutputStream);
    }
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_BACKWARD) {
        ackCommand(outputStream, EXTENDED_MOTION_DEVICE_HEADER, commandHeader);
        gotoSpline(pidMotion,
                -400.0f, 0.0f,
                0.0f,
                -100.0f, -100.0f,
                -MOTION_ACCELERATION_FACTOR_NORMAL, -MOTION_SPEED_FACTOR_NORMAL,
                true,
                notificationOutputStream);
    }
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_LEFT || commandHeader == COMMAND_MOTION_SPLINE_TEST_RIGHT) {
        ackCommand(outputStream, EXTENDED_MOTION_DEVICE_HEADER, commandHeader);
        float sign = 1.0f;
        if (commandHeader == COMMAND_MOTION_SPLINE_TEST_RIGHT) {
            sign = -sign;
        }
        gotoSpline(pidMotion,
						 400.0f, sign * 400.0f,
                         sign * 0.75f * PI,
                         200.0f, 200.0f,
                        MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL,
                         true,
					    notificationOutputStream);
    }
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_FORWARD_LEFT_FORWARD || commandHeader == COMMAND_MOTION_SPLINE_TEST_FORWARD_RIGHT_FORWARD) {
        ackCommand(outputStream, EXTENDED_MOTION_DEVICE_HEADER, commandHeader);
        float sign = 1.0f;
        if (commandHeader == COMMAND_MOTION_SPLINE_TEST_FORWARD_RIGHT_FORWARD) {
            sign = -sign;
        }
        gotoSpline(pidMotion,
						 1200.0f, sign * 600.0f,
                         0.0f,
                         1000.0f, 1000.0f,
                        MOTION_ACCELERATION_FACTOR_NORMAL, MOTION_SPEED_FACTOR_NORMAL,
                         true,
					    notificationOutputStream);
    }
    else if (commandHeader == COMMAND_MOTION_SPLINE_TEST_BACKWARD_LEFT_BACKWARD || commandHeader == COMMAND_MOTION_SPLINE_TEST_BACKWARD_RIGHT_BACKWARD) {
        ackCommand(outputStream, EXTENDED_MOTION_DEVICE_HEADER, commandHeader);
        float sign = 1.0f;
        if (commandHeader == COMMAND_MOTION_SPLINE_TEST_BACKWARD_LEFT_BACKWARD) {
            sign = -sign;
        }
        gotoSpline(pidMotion,
						 -1200.0f, -sign * 600.0f,
                         0.0f,
                         -1000.0f, -1000.0f,
                        -MOTION_ACCELERATION_FACTOR_NORMAL, -MOTION_SPEED_FACTOR_NORMAL,
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
