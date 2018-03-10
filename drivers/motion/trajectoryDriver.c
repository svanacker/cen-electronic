#include "trajectoryDriver.h"

#include <stdbool.h>

#include "../../common/2d/2d.h"

#include "../../common/io/buffer.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../device/motion/position/trajectoryDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

#include "../../robot/robot.h"

// SET TRAJECTORY

bool trajectoryDriverSetAbsolutePosition(float x, float y, float degree) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_TRAJECTORY_SET_ABSOLUTE_POSITION);
    appendHexFloat4(outputStream, x, POSITION_DIGIT_MM_PRECISION);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, y, POSITION_DIGIT_MM_PRECISION);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, degree, ANGLE_DIGIT_DEGREE_PRECISION);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// UPDATE TRAJECTORY DEVICE -> ROBOT POSITION
bool trajectoryDriverUpdateRobotPosition() {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, COMMAND_TRAJECTORY_GET_ABSOLUTE_POSITION);

    bool result = transmitFromDriverRequestBuffer();
    if (result) {
        float x = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        readHex(inputStream);
        float y = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        readHex(inputStream);
        float angle = readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION);

        updateRobotPosition(x, y, angle);
        return result;

    }
    return false;
}
