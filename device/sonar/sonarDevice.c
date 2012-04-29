#include "sonarDevice.h"
#include "sonarDeviceInterface.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

#include "../../drivers/sonar/srf02.h"
#include "../../common/delay/delay30F.h"

// DEVICE INTERFACE

void deviceSonarInit(void) {

}

void deviceSonarShutDown(void) {

}

unsigned int isSonarDeviceOk(void) {
    return getSRF02SoftwareRevision(SRF02_DEFAULT_ADDRESS) < 255;
    //	return getSRF02SoftwareRevisionDeprecated() < 255;
    // TODO :
    return TRUE;
}

unsigned char isSonarDeviceWithAddressOk(char addr) {
    return getSRF02SoftwareRevision(addr) < 255;
}

void deviceSonarHandleRawData(char header,
        InputStream* inputStream,
        OutputStream* outputStream) {
    if (header == COMMAND_GET_SONAR) {
        readHex2(inputStream);
        appendAck(outputStream);
        append(outputStream, COMMAND_GET_SONAR);
        int i;
        for (i = 0; i < 3; i++) {
            if (i > 0) {
                appendSeparator(outputStream);
            }
            int distance = getSRF02Distance();
            appendHex4(outputStream, distance);
        }
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
