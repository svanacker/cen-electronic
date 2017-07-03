#include <stdbool.h>

#include "ledDevice.h"
#include "ledDeviceInterface.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"
#include "../../common/log/logHandler.h"

#include "../device.h"


// DEVICE INTERFACE

void initLed( void ) {

}

void stopLed( void ) {

}

bool isLedDeviceOk ( void ) {
    return true;
}

unsigned int readLed(unsigned char ledIndex) {
    int value = 0;

    return value;
}

void deviceLedHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    if (commandHeader == COMMAND_WRITE_LED) {
        ackCommand(outputStream, LED_DEVICE_HEADER, COMMAND_WRITE_LED);

        unsigned char ledIndex = readHex2(inputStream);
        unsigned int value = readHex2(inputStream);
        
        setLedValue(ledIndex,value);
             
    }
        else if (commandHeader == COMMAND_TEST_LED) {
        ackCommand(outputStream, LED_DEVICE_HEADER, COMMAND_TEST_LED);
        
        testLedMainBoard();
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &initLed,
    .deviceShutDown = &stopLed,
    .deviceIsOk = &isLedDeviceOk,
    .deviceHandleRawData = &deviceLedHandleRawData,
};

DeviceDescriptor* getLedDeviceDescriptor() {
    return &descriptor;
}
