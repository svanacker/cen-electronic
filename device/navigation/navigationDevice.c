#include <stdbool.h>
#include <stdlib.h>

#include "navigationDevice.h"
#include "navigationDeviceInterface.h"

#include "../../common/error/error.h"
#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../device/device.h"

#include "../../navigation/navigation.h"
#include "../../navigation/location.h"
#include "../../navigation/locationList.h"

void deviceNavigationInit(void) {

}

void deviceNavigationShutDown(void) {
}

bool isNavigationDeviceOk(void) {
    return true;
}

void deviceNavigationHandleRawData(char commandHeader, InputStream* inputStream, OutputStream* outputStream){
    if (commandHeader == COMMAND_NAVIGATION_LOCATION_COUNT) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_LOCATION_COUNT);

        LocationList* locationList = getNavigationLocationList();
        unsigned int locationCount = getLocationCount(locationList);
        appendHex4(outputStream, locationCount);
    }
    else if (commandHeader == COMMAND_NAVIGATION_GET_LOCATION) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_GET_LOCATION);
        unsigned int locationIndex = readHex4(inputStream);
        LocationList* locationList = getNavigationLocationList();
        Location* location = getLocation(locationList, locationIndex);
        appendCharArray(outputStream, location->name, 4);
        appendSeparator(outputStream);
        appendHex4(outputStream, location->x);
        appendSeparator(outputStream);
        appendHex4(outputStream, location->y);
    }
    else if (commandHeader == COMMAND_NAVIGATION_LOCATION_CLEAR) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_GET_LOCATION);
        LocationList* locationList = getNavigationLocationList();
        clearLocationList(locationList);
    }
    else if (commandHeader == COMMAND_NAVIGATION_SET_LOCATION) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_SET_LOCATION);
        LocationList* locationList = getNavigationLocationList();
        // TODO : readCharArray(inputStream, xxxx ....)
        int x = readHex4(inputStream);
        int y = readHex4(inputStream);
        addLocation(locationList, NULL, x, y);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceNavigationInit,
    .deviceShutDown = &deviceNavigationShutDown,
    .deviceIsOk = &isNavigationDeviceOk,
    .deviceHandleRawData = &deviceNavigationHandleRawData,
};

DeviceDescriptor* getNavigationDeviceDescriptor() {
    return &descriptor;
}
