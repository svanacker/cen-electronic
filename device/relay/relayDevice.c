#include <stdbool.h>
#include <stdlib.h>

#include "relayDevice.h"
#include "relayDeviceInterface.h"

#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/error/error.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/pin.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../device/device.h"

#include "../../drivers/relay/relay.h"
#include "../../drivers/relay/relayDebug.h"

static Relay* relay;

void deviceRelayInit(void) {
    if (relay == NULL) {
        writeError(RELAY_NULL);
        return;
    }
    relay->relayInit(relay);
}

void deviceRelayShutDown(void) {
}

bool deviceRelayIsOk(void) {
    return true;
}

void deviceRelayHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    if (commandHeader == COMMAND_WRITE_RELAY) {
        ackCommand(outputStream, RELAY_DEVICE_HEADER, COMMAND_WRITE_RELAY);
        int relayIndex = readHex2(inputStream);
        checkIsSeparator(inputStream);
        bool value = readBool(inputStream);
        relay->relayWriteValue(relay, relayIndex, value);
    }
    else if (commandHeader == COMMAND_READ_RELAY) {
        ackCommand(outputStream, RELAY_DEVICE_HEADER, COMMAND_READ_RELAY);
        int relayIndex = readHex2(inputStream);
        bool value = relay->relayReadValue(relay, relayIndex);
        appendDec(outputStream, value);
    }
    else if (commandHeader == COMMAND_RELAY_DEBUG) {
        ackCommand(outputStream, RELAY_DEVICE_HEADER, COMMAND_RELAY_DEBUG);
        OutputStream* debugOutputStream = getDebugOutputStreamLogger();
        printRelayStatesTable(debugOutputStream, relay);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceRelayInit,
    .deviceShutDown = &deviceRelayShutDown,
    .deviceIsOk = &deviceRelayIsOk,
    .deviceHandleRawData = &deviceRelayHandleRawData,
};

DeviceDescriptor* getRelayDeviceDescriptor(Relay* relayParam) {
    relay = relayParam;
    return &descriptor;
}
