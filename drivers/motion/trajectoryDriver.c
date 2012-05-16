#include "trajectoryDriver.h"

#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../device/motion/position/trajectoryDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

// SET TRAJECTORY

BOOL trajectoryDriverSetAbsolutePosition(float x, float y, float deciDegree) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    append(outputStream, COMMAND_SET_ABSOLUTE_POSITION);
    appendHex4(outputStream, x);
	appendSeparator(outputStream);
    appendHex4(outputStream, y);
	appendSeparator(outputStream);
    appendHex4(outputStream, deciDegree);

    BOOL result = transmitFromDriverRequestBuffer();

    return result;
}
