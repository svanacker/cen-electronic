#include "robotInfraredDetectorDriver.h"

#include "../../common/commons.h"

#include "robotInfraredDetectorDeviceInterface.h"


#include "../../common/2d/2d.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../robot/opponent/robotInfraredDetectorDeviceInterface.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

BOOL robotInfraredDetectorHasObstacle() {
	OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* inputStream = getDriverResponseInputStream();

    append(outputStream, COMMAND_INFRARED_DETECTOR_DETECTION);

    BOOL result = transmitFromDriverRequestBuffer();
	if (result) {
        int result = readHex2(inputStream);
		return result != 0;
    }
    return FALSE;
}
