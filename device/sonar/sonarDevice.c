#include <stdbool.h>

#include "sonarDevice.h"
#include "sonarDeviceInterface.h"

#include "../../common/delay/cenDelay.h"

#include "../../common/io/inputStream.h"
#include "../../common/io/outputStream.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

#include "../../drivers/sonar/srf02.h"

#include "../../common/log/logger.h"
#include "../../common/log/logLevel.h"

static I2cBusConnection* sonarDeviceI2cBusConnection;

// DEVICE INTERFACE

void deviceSonarInit(void) {

}

void deviceSonarShutDown(void) {

}

bool isSonarDeviceOk(void) {
    return getSRF02SoftwareRevision(sonarDeviceI2cBusConnection, SRF02_DEFAULT_ADDRESS) < 255;
}

unsigned char isSonarDeviceWithAddressOk(char addr) {
    return getSRF02SoftwareRevision(sonarDeviceI2cBusConnection, addr) < 255;
}

void deviceSonarHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream) {
    if (commandHeader == COMMAND_GET_SONAR) {
        int sonarIndex = readHex2(inputStream);
        ackCommand(outputStream, SONAR_DEVICE_HEADER, COMMAND_GET_SONAR);
        int i;
        for (i = 0; i < 3; i++) {
            if (i > 0) {
                appendSeparator(outputStream);
            }
            int distance = getSRF02Distance(sonarDeviceI2cBusConnection, sonarIndex);
            appendHex4(outputStream, distance);
        }
    }
    else if (commandHeader == COMMAND_SONAR_CHANGE_ADDRESS) {
        int oldAddress = readHex2(inputStream);
        int newAddress = readHex2(inputStream);

        appendStringAndDec(getInfoOutputStreamLogger(), "\noldAddress=", oldAddress);
        appendStringAndDec(getInfoOutputStreamLogger(), "\newAddress=", newAddress);

        SRF02ChangeAddress(sonarDeviceI2cBusConnection, oldAddress, newAddress); 
        
        ackCommand(outputStream, SONAR_DEVICE_HEADER, COMMAND_SONAR_CHANGE_ADDRESS);
        append(outputStream, COMMAND_SONAR_CHANGE_ADDRESS);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceSonarInit,
    .deviceShutDown = &deviceSonarShutDown,
    .deviceIsOk = &isSonarDeviceOk,
    .deviceHandleRawData = &deviceSonarHandleRawData,
};

DeviceDescriptor* getSonarDeviceDescriptor(I2cBusConnection* i2cBusConnection) {
    sonarDeviceI2cBusConnection = i2cBusConnection;
    return &descriptor;
}
