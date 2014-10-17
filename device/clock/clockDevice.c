#include <peripheral/legacy/i2c_legacy.h>

#include "clock.h"
#include "clockDevice.h"
#include "clockDeviceInterface.h"

#include "../../common/cmd/commonCommand.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../drivers/clock/PCF8563.h"

void deviceClockInit(void) {
}

void deviceClockShutDown(void) {
}

bool isClockDeviceOk(void) {
    return true;
}

void deviceClockHandleRawData(char header, InputStream* inputStream, OutputStream* outputStream){
    if (header == COMMAND_READ_CLOCK) {
        Clock* clock = getGlobalClock();
        ackCommand(outputStream, CLOCK_DEVICE_HEADER, COMMAND_READ_CLOCK);
        appendHex2(outputStream, clock->hour);
        append(outputStream,':');
        appendHex2(outputStream, clock->minute);
        append(outputStream,':');
        appendHex2(outputStream, clock->second);
        append(outputStream,' ');
        appendHex2(outputStream, clock->day);
        append(outputStream,'/');
        appendHex2(outputStream, clock->month);
        append(outputStream,'/');
        appendHex2(outputStream, clock->year);
    } else if (header == COMMAND_WRITE_HOUR) {
        Clock* clock = getGlobalClock();
        clock->hour = readHex2(inputStream);
        clock->minute = readHex2(inputStream);
        clock->second = readHex2(inputStream);
        
        ackCommand(outputStream, CLOCK_DEVICE_HEADER, COMMAND_WRITE_HOUR);
        updateClockToHardware(clock);
    } else if (header == COMMAND_WRITE_DATE) {
        Clock* clock = getGlobalClock();
        clock->day = readHex2(inputStream);
        clock->month = readHex2(inputStream);
        clock->year = readHex2(inputStream);
        
        ackCommand(outputStream, CLOCK_DEVICE_HEADER, COMMAND_WRITE_DATE);
        updateClockToHardware(clock);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceClockInit,
    .deviceShutDown = &deviceClockShutDown,
    .deviceIsOk = &isClockDeviceOk,
    .deviceHandleRawData = &deviceClockHandleRawData,
};

DeviceDescriptor* getClockDeviceDescriptor() {
    return &descriptor;
}