#include <peripheral/legacy/i2c_legacy.h>

#include "clockDevice.h"
#include "clockDeviceInterface.h"

#include "../../common/clock/clock.h"
#include "../../common/cmd/commonCommand.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../drivers/clock/PCF8563.h"

static Clock* clock;

void deviceClockInit(void) {
}

void deviceClockShutDown(void) {
}

bool isClockDeviceOk(void) {
    return true;
}

void deviceClockHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream){
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