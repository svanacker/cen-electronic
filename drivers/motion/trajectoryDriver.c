#include "trajectoryDriver.h"

#include "../../common/commons.h"

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

bool trajectoryDriverSetAbsolutePosition(float x, float y, float deciDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_SET_ABSOLUTE_POSITION);
    appendHex4(outputStream, (int) x);
    appendSeparator(outputStream);
    appendHex4(outputStream, (int) y);
    appendSeparator(outputStream);
    appendHex4(outputStream, (int) deciDegree);

    bool result = transmitFromDriverRequestBuffer();

    return result;
}

// UPDATE TRAJECTORY DEVICE -> ROBOT POSITION
bool trajectoryDriverUpdateRobotPosition() {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, COMMAND_GET_ABSOLUTE_POSITION);

    bool result = transmitFromDriverRequestBuffer();
    if (result) {
        int x = readHex4(inputStream);
        readHex(inputStream);
        int y = readHex4(inputStream);
        readHex(inputStream);
        int angle = readHex4(inputStream);

        updateRobotPosition(x, y, angle);
        return result;

    }
    return false;
}
