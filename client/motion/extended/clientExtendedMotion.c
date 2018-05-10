#include "clientExtendedMotion.h"

#include "../../../common/2d/2d.h"

#include "../../../common/commons.h"

#include "../../../common/math/cenMath.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/ioUtils.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logHandler.h"

#include "../../../device/motion/extended/extendedMotionDeviceInterface.h"

#include "../../../drivers/driver.h"
#include "../../../drivers/driverList.h"
#include "../../../drivers/driverTransmitter.h"

bool clientExtendedMotionBSplineRelative(float x, float y, float angle, float dist0, float dist1, float accelerationFactor, float speedFactor) {
    appendStringLN(getDebugOutputStreamLogger(), "clientExtendedMotionBSplineRelative");
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, EXTENDED_MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_MOTION_SPLINE_RELATIVE);
    appendHexFloat6(outputStream, x, POSITION_DIGIT_MM_PRECISION);
    appendSeparator(outputStream);
    appendHexFloat6(outputStream, y, POSITION_DIGIT_MM_PRECISION);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, radToDeg(angle), ANGLE_DIGIT_DEGREE_PRECISION);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, dist0, BSPLINE_MOTION_DISTANCE_FACTOR_DIGIT);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, dist1, BSPLINE_MOTION_DISTANCE_FACTOR_DIGIT);
    appendSeparator(outputStream);
    appendHexFloat2(outputStream, accelerationFactor, BSPLINE_MOTION_ACCELERATION_FACTOR_DIGIT);
    appendSeparator(outputStream);
    appendHexFloat2(outputStream, speedFactor, BSPLINE_MOTION_SPEED_FACTOR_DIGIT);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool clientExtendedMotionBSplineAbsolute(float x, float y, float angleRadian, float dist0, float dist1, float accelerationFactor, float speedFactor) {
    appendStringLN(getDebugOutputStreamLogger(), "clientExtendedMotionBSplineAbsolute");
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, EXTENDED_MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_MOTION_SPLINE_ABSOLUTE);
    appendHexFloat6(outputStream, x, POSITION_DIGIT_MM_PRECISION);
    appendSeparator(outputStream);
    appendHexFloat6(outputStream, y, POSITION_DIGIT_MM_PRECISION);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, radToDeg(angleRadian), ANGLE_DIGIT_DEGREE_PRECISION);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, dist0, BSPLINE_MOTION_DISTANCE_FACTOR_DIGIT);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, dist1, BSPLINE_MOTION_DISTANCE_FACTOR_DIGIT);
    appendSeparator(outputStream);
    appendHexFloat2(outputStream, accelerationFactor, BSPLINE_MOTION_ACCELERATION_FACTOR_DIGIT);
    appendSeparator(outputStream);
    appendHexFloat2(outputStream, speedFactor, BSPLINE_MOTION_SPEED_FACTOR_DIGIT);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}


