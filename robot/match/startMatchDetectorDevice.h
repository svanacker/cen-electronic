#ifndef START_MATCH_DETECTOR_DEVICE_H
#define START_MATCH_DETECTOR_DEVICE_H

#include "../../device/device.h"
#include "../../common/io/outputStream.h"

/**
* Define a call back function which must be called during loopUntilStart.
*/
typedef unsigned char handleFunctionType(void);

/**
* Returns the deviceDescriptor of the end Match Detector.
*/
DeviceDescriptor* getStartMatchDetectorDeviceDescriptor();

/**
* Init the device.
*/
void initStartMatchDetector();

/**
* Indicates if the match is started or not.
*/
unsigned int isStartMatchDetectorOk();

/**
* Wait before start, but call the function given in argument.
*/
void loopUntilStart();

/**
* Test if the match is started or not.
*/
char isStarted();

/**
* Show the message to indicate that we wait for the match.
*/
void showWaitingStart(OutputStream* pcOutputStream);

/**
* Inform user that the match is started.
*/
void showStarted(OutputStream* pcOutputStream);

#endif
