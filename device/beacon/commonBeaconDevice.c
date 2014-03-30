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
#include "../../common/io/stream.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

#include "../../drivers/jennic/jennic5139Driver.h"
#include "../../drivers/jennic/jennic5139EventParser.h"

// Handle Input to Command Jennic or to ask the devices
static bool redirectToDevices = TRUE;

bool isCommandRedirectToDevices() {
	return redirectToDevices;
}

void setCommandRedirectToDevices() {
	redirectToDevices = TRUE;
}

// Device

void commonBeaconDeviceInit() {
	
}

void commonBeaconDeviceShutDown() {

}

bool commonBeaconDeviceIsOk() {
	return TRUE;
}

void commonBeaconDeviceHandleRawData(char header,
							 InputStream* inputStream,
							 OutputStream* outputStream) {
	// Redirect command to Jennic
	if (header == COMMAND_REDIRECT_TO_JENNIC) {
        appendAck(outputStream);
		redirectToDevices = FALSE;
		appendString(getOutputStreamLogger(INFO), "REDIRECT COMMAND TO JENNIC \n");
        append(outputStream, COMMAND_REDIRECT_TO_JENNIC);
	// Reset
	} else if (header == COMMAND_RESET_JENNIC) {
		appendAck(outputStream);
		jennic5139Reset();
        append(outputStream, COMMAND_RESET_JENNIC);
	// Local Jennic Light on/off
	} else if (header == COMMAND_LOCAL_LIGHT) {
		unsigned char status = readHex(inputStream);
        appendAck(outputStream);
		jennic5139LocalLight(JENNIC_LED_ALL, status != 0);
        append(outputStream, COMMAND_LOCAL_LIGHT);
	}
	// Print the data buffer
	else if (header == COMMAND_SHOW_DATA_FROM_JENNIC) {
        appendAck(outputStream);
		Buffer* inDataBuffer = getJennicInDataBuffer();
		copyInputToOutputStream(&(inDataBuffer->inputStream), getOutputStreamLogger(DEBUG), NULL, COPY_ALL);
        append(outputStream, COMMAND_SHOW_DATA_FROM_JENNIC);
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

