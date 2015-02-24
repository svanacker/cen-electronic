#include <stdbool.h>
#include <stdlib.h>

#include "clockDevice.h"
#include "clockDeviceInterface.h"

#include "../../common/clock/clock.h"
#include "../../common/error/error.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

static Clock* clock;

void _deviceClockCheckInitialized() {
    if (clock == NULL) {
        writeError(CLOCK_NULL);
    }
    if (!isClockInitialized(clock)) {
        writeError(CLOCK_NOT_INITIALIZED);
    }
}

void deviceClockInit(void) {
    _deviceClockCheckInitialized();
}

void deviceClockShutDown(void) {
}

bool isClockDeviceOk(void) {
    return true;
}

void deviceClockHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream){
    _deviceClockCheckInitialized();
    if (header == COMMAND_READ_CLOCK) {
        ackCommand(outputStream, CLOCK_DEVICE_HEADER, COMMAND_READ_CLOCK);
        ClockData* clockData = clock->readClock(clock);
        appendHex2(outputStream, clockData->hour);
        append(outputStream,':');
        appendHex2(outputStream, clockData->minute);
        append(outputStream,':');
        appendHex2(outputStream, clockData->second);
        append(outputStream,' ');
        appendHex2(outputStream, clockData->day);
        append(outputStream,'/');
        appendHex2(outputStream, clockData->month);
        append(outputStream,'/');
        appendHex2(outputStream, clockData->year);
    } else if (header == COMMAND_WRITE_HOUR) {
        ClockData* clockData = &(clock->clockData);
        clockData->hour = readHex2(inputStream);
        clockData->minute = readHex2(inputStream);
        clockData->second = readHex2(inputStream);
        
        ackCommand(outputStream, CLOCK_DEVICE_HEADER, COMMAND_WRITE_HOUR);
        clock->writeClock(clock);
    } else if (header == COMMAND_WRITE_DATE) {
        ClockData* clockData = &(clock->clockData);
        clockData->day = readHex2(inputStream);
        clockData->month = readHex2(inputStream);
        clockData->year = readHex2(inputStream);
        
        ackCommand(outputStream, CLOCK_DEVICE_HEADER, COMMAND_WRITE_DATE);
        clock->writeClock(clock);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceClockInit,
    .deviceShutDown = &deviceClockShutDown,
    .deviceIsOk = &isClockDeviceOk,
    .deviceHandleRawData = &deviceClockHandleRawData,
};

DeviceDescriptor* getClockDeviceDescriptor(Clock* clockParam) {
    clock = clockParam;
    return &descriptor;
}
