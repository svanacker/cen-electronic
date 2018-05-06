#include "clientTrajectory.h"

#include <stdbool.h>

#include "../../../common/2d/2d.h"

#include "../../../common/io/buffer.h"
#include "../../../common/io/ioUtils.h"
#include "../../../common/io/inputStream.h"
#include "../../../common/io/outputStream.h"
#include "../../../common/io/printWriter.h"
#include "../../../common/io/reader.h"

#include "../../../common/log/logger.h"
#include "../../../common/log/logHandler.h"

#include "../../../common/math/cenMath.h"

#include "../../../device/deviceConstants.h"
#include "../../../device/motion/position/trajectoryDeviceInterface.h"

#include "../../../drivers/driver.h"
#include "../../../drivers/driverList.h"
#include "../../../drivers/driverTransmitter.h"

#include "../../../robot/robot.h"

// SET TRAJECTORY

bool clientTrajectorySetAbsolutePosition(float x, float y, float radian) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    
    append(outputStream, TRAJECTORY_DEVICE_HEADER);
    append(outputStream, COMMAND_TRAJECTORY_SET_ABSOLUTE_POSITION);
    appendHexFloat6(outputStream, x, POSITION_DIGIT_MM_PRECISION);
    appendSeparator(outputStream);
    appendHexFloat6(outputStream, y, POSITION_DIGIT_MM_PRECISION);
    appendSeparator(outputStream);
    appendHexFloat4(outputStream, radToDeg(radian), ANGLE_DIGIT_DEGREE_PRECISION);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// UPDATE TRAJECTORY DEVICE -> ROBOT POSITION
bool clientTrajectoryUpdateRobotPosition() {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, TRAJECTORY_DEVICE_HEADER);    
    append(outputStream, COMMAND_TRAJECTORY_GET_ABSOLUTE_POSITION);

    bool result = transmitFromDriverRequestBuffer();
    if (result) {
        float x = readHexFloat6(inputStream, POSITION_DIGIT_MM_PRECISION);
        readHex(inputStream);
        float y = readHexFloat6(inputStream, POSITION_DIGIT_MM_PRECISION);
        readHex(inputStream);
        float angle = degToRad(readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION));

        updateRobotPosition(x, y, angle);
        return result;

    }
    return false;
}

// ADJUST
bool clientTrajectoryAdjustAngleToClosest(void) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, TRAJECTORY_DEVICE_HEADER);
    append(outputStream, COMMAND_TRAJECTORY_ADJUST_ANGLE_TO_CLOSEST);

    transmitFromDriverRequestBuffer();
    
    bool result = readBool(inputStream);
    
    return result;
}

bool clientTrajectoryAdjustXPosition(float x) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, TRAJECTORY_DEVICE_HEADER);
    append(outputStream, COMMAND_TRAJECTORY_ADJUST_X);
    appendHexFloat4(outputStream, x, POSITION_DIGIT_MM_PRECISION);
    
    transmitFromDriverRequestBuffer();
    
    bool result = readBool(inputStream);
    
    return result;
}

bool clientTrajectoryAdjustYPosition(float y) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, TRAJECTORY_DEVICE_HEADER);
    append(outputStream, COMMAND_TRAJECTORY_ADJUST_Y);
    appendHexFloat4(outputStream, y, POSITION_DIGIT_MM_PRECISION);
    
    transmitFromDriverRequestBuffer();
    
    bool result = readBool(inputStream);
    
    return result;
}
