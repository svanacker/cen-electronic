#include <stdlib.h>

#include "commonBeaconDevice.h"
#include "commonBeaconDeviceInterface.h"


#include "../../common/commons.h"

#include "../../common/cmd/commonCommand.h"

#include "../../common/io/buffer.h"
#include "../../common/io/inputStream.h"
#include "../../common/io/ioUtils.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../drivers/jennic/jennic5139Driver.h"
#include "../../drivers/jennic/jennic5139EventParser.h"

// Handle Input to Command Jennic or to ask the devices
static bool redirectToDevices = true;

bool isCommandRedirectToDevices() {
    return redirectToDevices;
}

void setCommandRedirectToDevices() {
    redirectToDevices = true;
}

// Device

void commonBeaconDeviceInit() {
    
}

void commonBeaconDeviceShutDown() {

}

bool commonBeaconDeviceIsOk() {
    return true;
}

void commonBeaconDeviceHandleRawData(char commandHeader,
                                     InputStream* inputStream,
                                     OutputStream* outputStream) {
    // Redirect command to Jennic
    if (commandHeader == COMMAND_REDIRECT_TO_JENNIC) {
        ackCommand(outputStream, COMMON_BEACON_DEVICE_HEADER, COMMAND_REDIRECT_TO_JENNIC);
        redirectToDevices = false;
        appendString(getOutputStreamLogger(INFO), "REDIRECT COMMAND TO JENNIC \n");
    // Reset
    } else if (commandHeader == COMMAND_RESET_JENNIC) {
        ackCommand(outputStream, COMMON_BEACON_DEVICE_HEADER, COMMAND_RESET_JENNIC);
        jennic5139Reset();
    // Local Jennic Light on/off
    } else if (commandHeader == COMMAND_LOCAL_LIGHT) {
        unsigned char status = readHex(inputStream);
        ackCommand(outputStream, COMMON_BEACON_DEVICE_HEADER, COMMAND_LOCAL_LIGHT);
        jennic5139LocalLight(JENNIC_LED_ALL, status != 0);
    }
    // Print the data buffer
    else if (commandHeader == COMMAND_SHOW_DATA_FROM_JENNIC) {
        ackCommand(outputStream, COMMON_BEACON_DEVICE_HEADER, COMMAND_SHOW_DATA_FROM_JENNIC);
        Buffer* inDataBuffer = getJennicInDataBuffer();
        copyInputToOutputStream(&(inDataBuffer->inputStream), getOutputStreamLogger(DEBUG), NULL, COPY_ALL);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &commonBeaconDeviceInit,
    .deviceShutDown = &commonBeaconDeviceShutDown,
    .deviceIsOk = &commonBeaconDeviceIsOk,
    .deviceHandleRawData = &commonBeaconDeviceHandleRawData
};

DeviceDescriptor* getCommonBeaconDeviceDescriptor() {
    return &descriptor;
}

