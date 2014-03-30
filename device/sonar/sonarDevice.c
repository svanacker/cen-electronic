#include "sonarDevice.h"
#include "sonarDeviceInterface.h"

#include "../../common/delay/delay30F.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

#include "../../drivers/sonar/srf02.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"


// DEVICE INTERFACE

void deviceSonarInit(void) {

}

void deviceSonarShutDown(void) {

}

bool isSonarDeviceOk(void) {
    return getSRF02SoftwareRevision(SRF02_DEFAULT_ADDRESS) < 255;
}

unsigned char isSonarDeviceWithAddressOk(char addr) {
    return getSRF02SoftwareRevision(addr) < 255;
}

void deviceSonarHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (header == COMMAND_GET_SONAR) {
        int sonarIndex = readHex2(inputStream);
        appendAck(outputStream);
        append(outputStream, COMMAND_GET_SONAR);
        int i;
        for (i = 0; i < 3; i++) {
            if (i > 0) {
                appendSeparator(outputStream);
            }
            int distance = getSRF02Distance(sonarIndex);
            appendHex4(outputStream, distance);
        }
    }
	else if (header == COMMAND_SONAR_CHANGE_ADDRESS) {
        int oldAddress = readHex2(inputStream);
        int newAddress = readHex2(inputStream);

		appendStringAndDec(getOutputStreamLogger(ALWAYS), "\noldAddress=", oldAddress);
		appendStringAndDec(getOutputStreamLogger(ALWAYS), "\newAddress=", newAddress);

        SRF02ChangeAddress(oldAddress, newAddress); 
		
        appendAck(outputStream);
        append(outputStream, COMMAND_SONAR_CHANGE_ADDRESS);
	}
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceSonarInit,
    .deviceShutDown = &deviceSonarShutDown,
    .deviceIsOk = &isSonarDeviceOk,
    .deviceHandleRawData = &deviceSonarHandleRawData,
};

DeviceDescriptor* getSonarDeviceDescriptor() {
    return &descriptor;
}
