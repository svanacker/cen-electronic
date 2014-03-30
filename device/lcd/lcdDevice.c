#include "lcdDevice.h"
#include "lcdDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"
#include "../../common/io/stream.h"

#include "../../drivers/lcd/lcd.h"

void deviceLCDInit() {
}

void deviceLCDShutDown() {
}

bool deviceLCDIsOk() {
    return TRUE;
}

void deviceLCDHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (header == COMMAND_LCD) {
        int lcdTextLength = readHex2(inputStream);
        appendAck(outputStream);
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
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceLCDInit,
    .deviceShutDown = &deviceLCDShutDown,
    .deviceIsOk = &deviceLCDIsOk,
    .deviceHandleRawData = &deviceLCDHandleRawData,
};

DeviceDescriptor* getLCDDeviceDescriptor() {
    return &descriptor;
}
