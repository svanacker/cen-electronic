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
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"

// TEMP

#define NAVIGATION_LOCATION_LIST_ARRAY_LENGTH        30
#define NAVIGATION_PATH_LIST_TEST_ARRAY_LENGTH       30
#define BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH        30

static LocationList locationList;
static Location locationListArray[NAVIGATION_LOCATION_LIST_ARRAY_LENGTH];

static PathList pathList;
static PathData pathListArray[NAVIGATION_PATH_LIST_TEST_ARRAY_LENGTH];

static BitList outgoingPathBitList;
static unsigned int outgoingPathBitArray[BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH];
static BitList availablePathBitList;
static unsigned int availablePathBitArray[BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH];

void deviceNavigationInit(void) {

    initLocationList(&locationList, (Location(*)[]) &locationListArray, NAVIGATION_LOCATION_LIST_ARRAY_LENGTH);
    initPathList(&pathList, (PathData(*)[]) &pathListArray, NAVIGATION_PATH_LIST_TEST_ARRAY_LENGTH);
    initBitList(&outgoingPathBitList, (unsigned int(*)[]) &outgoingPathBitArray, BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH);
    initBitList(&availablePathBitList, (unsigned int(*)[]) &availablePathBitArray, BIT_LIST_NAVIGATION_TEST_ARRAY_LENGTH);

    initNavigation(&locationList, &pathList, &outgoingPathBitList, &availablePathBitList);
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
        appendFixedCharArray(outputStream, &(location->name));
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
        unsigned int index = readHex4(inputStream);
        checkIsSeparator(inputStream);
        FixedCharArray tempCharArray;
        readFixedCharArray(inputStream, &tempCharArray);
        checkIsSeparator(inputStream);
        int x = readHex4(inputStream);
        checkIsSeparator(inputStream);
        int y = readHex4(inputStream);
        addLocation(locationList, &tempCharArray, x, y);
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
