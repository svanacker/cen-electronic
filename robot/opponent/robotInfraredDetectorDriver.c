#include "robotInfraredDetectorDriver.h"

#include "../../common/commons.h"

#include "robotInfraredDetector.h"
#include "robotInfraredDetectorDeviceInterface.h"

#include "../../common/2d/2d.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../device/deviceConstants.h"

#include "../../robot/opponent/robotInfraredDetectorDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

bool robotInfraredDetectorHasObstacle(enum InfraredDetectorGroupType type) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, ROBOT_INFRARED_DETECTOR_DEVICE_HEADER);
    append(outputStream, COMMAND_INFRARED_DETECTOR_DETECTION);
    appendHex2(outputStream, type);
    bool result = transmitFromDriverRequestBuffer();
    if (result) {
        int result = readHex2(inputStream);
        return result == 0x01;
    }
    return false;
}
