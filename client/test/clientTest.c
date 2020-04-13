#include "clientTest.h"

#include "../../common/commons.h"

#include "../../common/io/buffer.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logHandler.h"

#include "../../drivers/driver.h"
#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

#include "../../device/test/testDeviceInterface.h"

unsigned char clientTestAdd(unsigned char value1, unsigned char value2) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, TEST_DEVICE_HEADER);
    append(outputStream, COMMAND_TEST);
    appendHex2(outputStream, value1);
    appendHex2(outputStream, value2);
    
    if (transmitFromDriverRequestBuffer()) {
        InputStream* inputStream = getDriverResponseInputStream();
        return readHex2(inputStream);
    }
    return 0x00;
}
