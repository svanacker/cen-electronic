#include "clientIO.h"

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

#include "../../common/io/pin.h"
#include "../../device/io/ioDeviceInterface.h"

bool clientIORead(unsigned char pinIndex, bool* value) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, IO_DEVICE_HEADER);
    append(outputStream, COMMAND_IO_READ);
    appendHex2(outputStream, pinIndex);
    
    bool result = transmitFromDriverRequestBuffer();
    if (result) {
        InputStream* inputStream = getDriverResponseInputStream();
        *value = readBool(inputStream);
        }
    return result;
}

bool clientIOWrite(unsigned char pinIndex, bool value) {
    OutputStream* outputStream = getDriverRequestOutputStream();

    append(outputStream, IO_DEVICE_HEADER);
    append(outputStream, COMMAND_IO_WRITE);
    appendHex2(outputStream, pinIndex);
    appendSeparator(outputStream);
    appendBool(outputStream, value);
    
    bool result = transmitFromDriverRequestBuffer();

    return result;
}


