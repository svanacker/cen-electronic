#ifndef END_MATCH_DETECTOR_DEVICE_H
#define END_MATCH_DETECTOR_DEVICE_H

#include "../../device/device.h"

#include "../../robot/config/robotConfig.h"

#define MATCH_DURATION 85

/**
* Defines the index for the timer which detects end of the match.
*/
#define END_MATCH_DETECTOR_TIMER_CODE 20

/**
* Returns the deviceDescriptor of the end Match Detector.
* @param we need the robotConfig to know if we end the match or not !
*/
DeviceDescriptor* getEndMatchDetectorDeviceDescriptor(RobotConfig* robotConfigParam);

/**
* Indicates that the match begins.
*/
void markStartMatch( void );

void resetStartMatch(void);

/**
* Get the current time for the match.
*/
int getCurrentTimeInSecond ( void );

/**
* Ask to know if the match is ending.
* @return true if the match is ending
*/
bool isEnd( void );

/**
* Write into the stream that the match is finished.
* @param outputStream the outputStream in which we write the end
*/
void showEnd(OutputStream* outputStream);

#endif


