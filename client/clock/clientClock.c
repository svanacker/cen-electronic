#include "clientClock.h"

#include <stdbool.h>

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/clock/clock.h"
#include "../../device/clock/clockDeviceInterface.h"

#include "../../drivers/driverList.h"
#include "../../drivers/driverTransmitter.h"

bool clientClockGetClockData(ClockData* clockData) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    InputStream* resultStream = getDriverResponseInputStream();
    append(outputStream, CLOCK_DEVICE_HEADER);
    append(outputStream, COMMAND_READ_CLOCK);

    bool result = transmitFromDriverRequestBuffer();
    if (result) {
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
    }
    return result;
}

bool clientClockWriteHourRemoteClockData(ClockData* clockData, int dispatcherIndex) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    // InputStream* resultStream = getDriverResponseInputStream();

    // To select the Dispatcher
    append(outputStream, DISPATCHER_COMMAND_HEADER);
    appendHex2(outputStream, dispatcherIndex);

    // The device / command Header + Data
    append(outputStream, CLOCK_DEVICE_HEADER);
    append(outputStream, COMMAND_WRITE_TIME);
    appendHex2(outputStream, clockData->hour);
    appendHex2(outputStream, clockData->minute);
    appendHex2(outputStream, clockData->second);
    bool result = transmitFromDriverRequestBuffer();

    return result;
}

bool clientClockWriteDateRemoteClockData(ClockData* clockData, int dispatcherIndex) {
    OutputStream* outputStream = getDriverRequestOutputStream();
    // InputStream* resultStream = getDriverResponseInputStream();

    // To select the Dispatcher
    append(outputStream, DISPATCHER_COMMAND_HEADER);
    appendHex2(outputStream, dispatcherIndex);

    // The device / command Header + Data
    append(outputStream, CLOCK_DEVICE_HEADER);
    append(outputStream, COMMAND_WRITE_DATE);
    appendHex2(outputStream, clockData->day);
    appendHex2(outputStream, clockData->month);
    appendHex2(outputStream, clockData->year);
    bool result = transmitFromDriverRequestBuffer();

    return result;
}
