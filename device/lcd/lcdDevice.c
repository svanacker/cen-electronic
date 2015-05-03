#include <stdbool.h>

#include "lcdDevice.h"
#include "lcdDeviceInterface.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../drivers/lcd/lcd.h"

void deviceLCDInit(void) {
}

void deviceLCDShutDown(void) {
}

bool deviceLCDIsOk(void) {
    return true;
}

void deviceLCDHandleRawData(char commandHeader,
                            InputStream* inputStream,
                            OutputStream* outputStream) {
    if (commandHeader == COMMAND_LCD) {
        int lcdTextLength = readHex2(inputStream);
        ackCommand(outputStream, LCD_DEVICE_HEADER, COMMAND_LCD);
        // print character
        int i;
        for (i = 0; i < LCD_CHAR_COUNT_BY_MESSAGE; i++) {
            int c = readHex2(inputStream);
            // we only valid write data (we respect the length gived after the header)
            if (i < lcdTextLength) {
                writeLCDChar(c);
            }
        }
    }
    else if (commandHeader == COMMAND_CLEAR_LCD) {
        ackCommand(outputStream, LCD_DEVICE_HEADER, COMMAND_CLEAR_LCD);
        clearScreen();
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceLCDInit,
    .deviceShutDown = &deviceLCDShutDown,
    .deviceIsOk = &deviceLCDIsOk,
    .deviceHandleRawData = &deviceLCDHandleRawData,
};

DeviceDescriptor* getLCDDeviceDescriptor(void) {
    return &descriptor;
}
