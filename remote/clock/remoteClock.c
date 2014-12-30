#include "remoteClock.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/clock/clock.h"
#include "../../device/clock/clockDeviceInterface.h"

#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

void getRemoteClockData(ClockData* clockData) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* resultStream = getDriverResponseInputStream();
    append(outputStream, CLOCK_DEVICE_HEADER);
    append(outputStream, COMMAND_READ_CLOCK);

    bool ok = transmitFromDriverRequestBuffer();
    if (ok) {
        clockData->hour = readHex2(resultStream);
        resultStream->readChar(resultStream);

        clockData->minute = readHex2(resultStream);
        resultStream->readChar(resultStream);

        clockData->second = readHex2(resultStream);
        resultStream->readChar(resultStream);

        clockData->day = readHex2(resultStream);
        resultStream->readChar(resultStream);

        clockData->month = readHex2(resultStream);
        resultStream->readChar(resultStream);

        clockData->year = readHex2(resultStream);
        resultStream->readChar(resultStream);
    }
}
