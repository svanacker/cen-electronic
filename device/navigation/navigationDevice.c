#include <stdbool.h>
#include <stdlib.h>

#include "navigationDevice.h"
#include "navigationDeviceInterface.h"

#include "../../common/2d/2d.h"

#include "../../common/error/error.h"

#include "../../common/io/printWriter.h"
#include "../../common/io/reader.h"

#include "../../common/log/logger.h"

#include "../../common/math/cenMath.h"

#include "../../device/device.h"

#include "../../motion/motion.h"
#include "../../motion/extended/bsplineMotion.h"

#include "../../navigation/navigation.h"
#include "../../navigation/navigationDebug.h"
#include "../../navigation/navigationComputer.h"
#include "../../navigation/location.h"
#include "../../navigation/locationListDebug.h"
#include "../../navigation/path.h"
#include "../../navigation/pathList.h"
#include "../../navigation/pathListDebug.h"

// Forward declaration
Navigation* getNavigationDeviceNavigationObject(void);

void deviceNavigationInit(void) {

}

void deviceNavigationShutDown(void) {
}

bool isNavigationDeviceOk(void) {
    return true;
}

void deviceNavigationHandleRawData(unsigned char commandHeader, InputStream* inputStream, OutputStream* outputStream, OutputStream* notificationOutputStream) {
    // Locations
    if (commandHeader == COMMAND_NAVIGATION_LOCATION_COUNT) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_LOCATION_COUNT);
        Navigation* navigation = getNavigationDeviceNavigationObject();
        LocationList* locationList = getNavigationLocationList(navigation);
        unsigned int locationCount = getLocationCount(locationList);
        appendHex4(outputStream, locationCount);
    }
    else if (commandHeader == COMMAND_NAVIGATION_GET_LOCATION) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_GET_LOCATION);
        unsigned int locationIndex = readHex4(inputStream);
        Navigation* navigation = getNavigationDeviceNavigationObject();
        LocationList* locationList = getNavigationLocationList(navigation);
        Location* location = getLocation(locationList, locationIndex);
        appendHexFixedCharArray(outputStream, &(location->name));
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, location->x, POSITION_DIGIT_MM_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, location->y, POSITION_DIGIT_MM_PRECISION);
    }
    else if (commandHeader == COMMAND_NAVIGATION_LOCATION_CLEAR) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_GET_LOCATION);
        Navigation* navigation = getNavigationDeviceNavigationObject();
        LocationList* locationList = getNavigationLocationList(navigation);
        clearLocationList(locationList);
    }
    else if (commandHeader == COMMAND_NAVIGATION_SET_LOCATION) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_SET_LOCATION);
        Navigation* navigation = getNavigationDeviceNavigationObject();
        LocationList* locationList = getNavigationLocationList(navigation);
        FixedCharArray locationNameFixedCharArray;
		readHexFixedCharArray(inputStream, &locationNameFixedCharArray);
        checkIsSeparator(inputStream);
        float x = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        checkIsSeparator(inputStream);
        float y = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);

        // Find an existing location if any to update or create if it doesn't find
        Location* location = findLocationByName(locationList, &locationNameFixedCharArray);
        if (location == NULL) {
            addLocation(locationList, &locationNameFixedCharArray, "", x, y);
        }
        else {
            copyFixedCharArray(&locationNameFixedCharArray, &(location->name));
            location->x = x;
            location->y = y;
        }
    }
	else if (commandHeader == COMMAND_NAVIGATION_LOCATION_LIST_DEBUG) {
		ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_LOCATION_LIST_DEBUG);
        Navigation* navigation = getNavigationDeviceNavigationObject();
		LocationList* locationList = getNavigationLocationList(navigation);
		printLocationListTable(getInfoOutputStreamLogger(), locationList);
	}
	else if (commandHeader == COMMAND_NAVIGATION_LOCATION_ADD_TESTS_DATA) {
		ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_LOCATION_ADD_TESTS_DATA);
        Navigation* navigation = getNavigationDeviceNavigationObject();
		LocationList* locationList = getNavigationLocationList(navigation);
		addLocationListTestsData(locationList);
	}
    // Paths
    else if (commandHeader == COMMAND_NAVIGATION_PATH_COUNT) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_PATH_COUNT);
        Navigation* navigation = getNavigationDeviceNavigationObject();
        PathList* pathList = navigation->paths;
        unsigned int pathCount = getPathCount(pathList);
        appendHex4(outputStream, pathCount);
    }
    else if (commandHeader == COMMAND_NAVIGATION_GET_PATH) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_GET_PATH);
        unsigned int pathIndex = readHex4(inputStream);
        Navigation* navigation = getNavigationDeviceNavigationObject();
        PathList* pathList = navigation->paths;
        PathData* pathData = getPath(pathList, pathIndex);

        Location* location1 = pathData->location1;
        if (location1 == NULL) {
            writeError(LOCATION_DOES_NOT_EXIST);
            appendString(outputStream, "\0\0\0\0");
        }
        else {
            FixedCharArray* locationName1 = &(location1->name);
			appendHexFixedCharArray(outputStream, locationName1);
        }
        appendSeparator(outputStream);

        Location* location2 = pathData->location2;
        if (location2 == NULL) {
            writeError(LOCATION_DOES_NOT_EXIST);
            appendString(outputStream, "\0\0\0\0");
        }
        else {
            FixedCharArray* locationName2 = &(location2->name);
			appendHexFixedCharArray(outputStream, locationName2);
        }
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, pathData->cost, 0);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, pathData->controlPointDistance1, POSITION_DIGIT_MM_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, pathData->controlPointDistance2, POSITION_DIGIT_MM_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, radToDeg(pathData->angleRadian1), ANGLE_DIGIT_DEGREE_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, radToDeg(pathData->angleRadian2), ANGLE_DIGIT_DEGREE_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, pathData->accelerationFactor, ACCELERATION_MM_BY_SEC_2_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendHexFloat4(outputStream, pathData->speedFactor, SPEED_MM_BY_SEC_DIGIT_PRECISION);
        appendSeparator(outputStream);
        appendBool(outputStream, pathData->mustGoBackward);
    }
    else if (commandHeader == COMMAND_NAVIGATION_PATH_CLEAR) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_PATH_CLEAR);
        Navigation* navigation = getNavigationDeviceNavigationObject();
        PathList* pathList = navigation->paths;
        clearPathList(pathList);
    }
    else if (commandHeader == COMMAND_NAVIGATION_SET_PATH) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_SET_PATH);
        Navigation* navigation = getNavigationDeviceNavigationObject();
        PathList* pathList = getNavigationPathList(navigation);
        LocationList* locationList = getNavigationLocationList(navigation);

        FixedCharArray tempLocationName1;
		readHexFixedCharArray(inputStream, &tempLocationName1);
        checkIsSeparator(inputStream);
        FixedCharArray tempLocationName2;
		readHexFixedCharArray(inputStream, &tempLocationName2);
        checkIsSeparator(inputStream);


        Location* location1 = findLocationByName(locationList, &tempLocationName1);
        if (location1 == NULL) {
            writeError(LOCATION_DOES_NOT_EXIST);
        }

        Location* location2 = findLocationByName(locationList, &tempLocationName2);
        if (location2 == NULL) {
            writeError(LOCATION_DOES_NOT_EXIST);
        }

        // TODO : Must returns a different path if reversed ?
        PathData* pathData = getPathOfLocations(pathList, location1, location2);

        // Create if does not exist
        if (pathData == NULL) {
            pathData = addPath(pathList);
        }
        pathData->location1 = location1;
        pathData->location2 = location2;

        pathData->cost = readHexFloat4(inputStream, 0);
        checkIsSeparator(inputStream);
        pathData->controlPointDistance1 = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        checkIsSeparator(inputStream);
        pathData->controlPointDistance2 = readHexFloat4(inputStream, POSITION_DIGIT_MM_PRECISION);
        checkIsSeparator(inputStream);
        pathData->angleRadian1 = degToRad(readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION));
        checkIsSeparator(inputStream);
        pathData->angleRadian2 = degToRad(readHexFloat4(inputStream, ANGLE_DIGIT_DEGREE_PRECISION));
        checkIsSeparator(inputStream);
        pathData->accelerationFactor = readHexFloat4(inputStream, ACCELERATION_MM_BY_SEC_2_DIGIT_PRECISION);
        checkIsSeparator(inputStream);
        pathData->speedFactor = readHexFloat4(inputStream, SPEED_MM_BY_SEC_DIGIT_PRECISION);
        checkIsSeparator(inputStream);
        pathData->mustGoBackward = readBool(inputStream);
    }
    else if (commandHeader == COMMAND_NAVIGATION_PATH_GO) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_PATH_GO);
        unsigned int pathIndex = readHex2(inputStream);
        Navigation* navigation = getNavigationDeviceNavigationObject();
        PathList* pathList = getNavigationPathList(navigation);
        PathData* pathData = getPath(pathList, pathIndex);
        moveAlongPath(pathData);
    }
	else if (commandHeader == COMMAND_NAVIGATION_PATH_LIST_DEBUG) {
		ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_PATH_LIST_DEBUG);
        Navigation* navigation = getNavigationDeviceNavigationObject();
		PathList* pathList = getNavigationPathList(navigation);
		printPathListTable(getInfoOutputStreamLogger(), pathList);
	}
	else if (commandHeader == COMMAND_NAVIGATION_PATH_LIST_ADD_TESTS_DATA) {
		ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_PATH_LIST_ADD_TESTS_DATA);
        Navigation* navigation = getNavigationDeviceNavigationObject();
		LocationList* locationList = getNavigationLocationList(navigation);
		PathList* pathList = getNavigationPathList(navigation);
		addPathListTestsData(pathList, locationList);
	}
    else if (commandHeader == COMMAND_NAVIGATION_LOCATION_LIST_AND_OUTGOING_PATHS) {
        ackCommand(outputStream, NAVIGATION_DEVICE_HEADER, COMMAND_NAVIGATION_LOCATION_LIST_AND_OUTGOING_PATHS);
        Navigation* navigation = getNavigationDeviceNavigationObject();
        printNavigationDebugLocationAndOutgoingPathListTable(getInfoOutputStreamLogger(), navigation);
    }
}

static DeviceDescriptor descriptor = {
    .deviceInit = &deviceNavigationInit,
    .deviceShutDown = &deviceNavigationShutDown,
    .deviceIsOk = &isNavigationDeviceOk,
    .deviceHandleRawData = &deviceNavigationHandleRawData,
};

Navigation* getNavigationDeviceNavigationObject(void) {
    return (Navigation*)descriptor.object;
}

DeviceDescriptor* getNavigationDeviceDescriptor(Navigation* navigationParam) {
    descriptor.object = (int*) navigationParam;
    return &descriptor;
}
