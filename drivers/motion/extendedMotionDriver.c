#include "extendedMotionDriver.h"

#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../device/motion/extended/extendedMotionDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

bool motionDriverBSplineRelative(float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_MOTION_SPLINE_RELATIVE);
    appendHex4(outputStream, (signed int) x);
    appendSeparator(outputStream);
    appendHex4(outputStream, (signed int) y);
    appendSeparator(outputStream);
    appendHex4(outputStream, (signed int) angle);
    appendSeparator(outputStream);
    appendHex2(outputStream, (char) dist0);
    appendSeparator(outputStream);
    appendHex2(outputStream, (char) dist1);
    appendSeparator(outputStream);
    appendHex(outputStream, (char) accelerationFactor);
    appendHex(outputStream, (char) speedFactor);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool motionDriverBSplineAbsolute(float x, float y, float angle, float dist0, float dist1, int accelerationFactor, int speedFactor) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, MOTION_DEVICE_HEADER);
    append(outputStream, COMMAND_MOTION_SPLINE_ABSOLUTE);
    appendHex4(outputStream, (signed int) x);
    appendSeparator(outputStream);
    appendHex4(outputStream, (signed int) y);
    appendSeparator(outputStream);
    appendHex4(outputStream, (signed int) angle);
    appendSeparator(outputStream);
    appendHex2(outputStream, (char) dist0);
    appendSeparator(outputStream);
    appendHex2(outputStream, (char) dist1);
    appendSeparator(outputStream);
    appendHex(outputStream, (char) accelerationFactor);
    appendHex(outputStream, (char) speedFactor);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}


